/**
 * Fichier lcd_lvgl.c du projet qui contient tout ce qu'il faut pour la gestion de l'interface graphique et de ses modules communs (DMA). Elle contient une fonction "main"
 * (lvgl_init) qui s'occupe de démarrer et de configurer le tout. Elle appel en autre la librairie HAL de STM pour l'initialisation du "driver" de l'écran, le DSI, le LTDC et
 * la SDRAM. Pour le reste, elle configure le DMA2D et utilise le DMA configurer dans le main (il faudrait apporter la configuration du DMA du main dans ce fichier).
 *
 * Sinon, elle initialise la librairie graphique little_lvgl et lie les fonctions nécessaire à cette dernière. Le fichier contient aussi les "callbacks" des modules DMA
 * et LTDC.
 *
 * Selon la configuration de la librairie lvgl (lv_conf.h) le fichier peut configurer l'écran de façon à utiliser l'écran en ARGB8888 et RGB565 (RGB565 pas 100% fonctionnel,
 * il faut désactiver l'accéleration GPU sinon la couleur n'est pas bonne).
 *
 * @Christopher Bullock-D'Arcy
 * @version 1.0
 * @Date 19 mars 2018
 */

/*********************
*      INCLUDES
*********************/
#include <stdio.h>

#include "lv_conf.h"
#include "lvgl/lv_core/lv_vdb.h"
#include "lvgl/lv_hal/lv_hal.h"
#include <string.h>

#include "lcd_lvgl.h"

#include "../Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_lcd.h"
#include "../Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_ts.h"

/*********************
*      DEFINES
*********************/



/**********************
*      TYPEDEFS
**********************/


/**********************
*  STATIC PROTOTYPES
**********************/


/**********************
*  STATIC PROTOTYPES
**********************/
//Prototype
/*These 3 functions are needed by LittlevGL*/
static void tft_fill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color);
static void tft_map(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p);
static void tft_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p);
#if USE_LV_GPU != 0
static void DMA2D_Config(void);
static void gpu_mem_blend(lv_color_t * dest, const lv_color_t * src, uint32_t length, lv_opa_t opa);
static void gpu_mem_fill(lv_color_t * dest, uint32_t length, lv_color_t color);
#endif

//TouchScreen
static bool touchpad_read(lv_indev_data_t *data);

/**********************
*  STATIC VARIABLES
**********************/
//Écran LCD
#if LV_COLOR_DEPTH == 24
	#if TFT_EXT_FB != 0
	__IO uint32_t * my_fb = (__IO uint32_t*) (SDRAM_BANK_ADDR);
	#else
	static uint32_t my_fb[TFT_HOR_RES * TFT_VER_RES];
	#endif
#elif LV_COLOR_DEPTH == 16
	#if TFT_EXT_FB != 0
	static __IO uint16_t * my_fb = (__IO uint16_t*) (SDRAM_BANK_ADDR);
	#else
	static uint16_t my_fb[TFT_HOR_RES * TFT_VER_RES];
	#endif
#endif


static int32_t x1_flush;
static int32_t y1_flush;
static int32_t x2_flush;
static int32_t y2_fill;
static int32_t y_fill_act;
static const lv_color_t * buf_to_flush;

//TouchScreen
static TS_StateTypeDef  TS_State;

#if USE_LV_GPU != 0
static DMA2D_HandleTypeDef *Dma2dHandle;
#endif

lv_indev_drv_t indev_drv;

/**********************
*  GLOBAL VARIABLES
**********************/
DMA_HandleTypeDef *DMA_M2M;

/**********************
*      MACROS
**********************/

/**********************
*   GLOBAL FUNCTIONS
**********************/

/**
* @brief  Fonction d'initialisation pour la configuration complète du module LCD
* @param  dma_handle: contient la configuration complète du DMA numéro 2 fait dans le main
* @param  dma2d_handle: contient la configuration complète du DMA2D fait dans le main
* @note   La fonction utilise les drivers que STM32 fournis dans le HAL
* @retval Rien
*/
void lvgl_init(DMA_HandleTypeDef *dma_handle, DMA2D_HandleTypeDef *dma2d_handle)
{
	DMA_M2M = dma_handle;
	#if USE_LV_GPU != 0
	Dma2dHandle = dma2d_handle;
	#endif

	lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);

#if TFT_EXT_FB != 0
	//BSP_SDRAM_Init();  //Initialisé lors de l'init de l'écran
#endif
	BSP_LCD_InitEx(LCD_ORIENTATION_PORTRAIT); //LCD_ORIENTATION_LANDSCAPE); //Ne change rien avec l'écran AMOLED

#if LV_COLOR_DEPTH == 24
	BSP_LCD_LayerDefaultInit(0, (uint32_t) my_fb);
#elif LV_COLOR_DEPTH == 16
	BSP_LCD_LayerDefaultInit(0, (uint32_t) my_fb);
#endif

	BSP_LCD_Clear(LCD_COLOR_WHITE);

	disp_drv.disp_fill = tft_fill;
	disp_drv.disp_map = tft_map;
	disp_drv.disp_flush = tft_flush;
#if USE_LV_GPU != 0
	DMA2D_Config();
	disp_drv.mem_blend = gpu_mem_blend;
	disp_drv.mem_fill = gpu_mem_fill;
#endif
	lv_disp_drv_register(&disp_drv);

	// Debug setting pour voir si les méthode d'écriture sur le lcd fonctionnent tjrs
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	BSP_LCD_FillRect(1, 1, 250, 250);

	BSP_LCD_SetTextColor(LCD_COLOR_ORANGE);
	BSP_LCD_FillRect(250, 250, 150, 150);

	BSP_LCD_DisplayStringAt(10,210,"Test de l'écran AMOLED", CENTER_MODE);

	HAL_Delay(1000);

	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	BSP_LCD_FillRect(1, 1, 150, 150);

	BSP_LCD_SetTextColor(LCD_COLOR_ORANGE);
	BSP_LCD_FillRect(150, 150, 150, 150);

	BSP_LCD_DisplayStringAt(30,150,"Test de l'ecran AMOLED", CENTER_MODE);
	BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());

    lv_indev_drv_init(&indev_drv);
    indev_drv.read = touchpad_read;
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    lv_indev_drv_register(&indev_drv);

    //BSP_LCD_SwapBuffer(); //Fonction qui programme l'interuption sur une ligne de l'écran et refresh le changement

} 						  //sur la synchronisation verticale

#if USE_LV_GPU != 0
/**
* @brief  DMA2D Transfer completed callback
* @param  hdma2d: DMA2D handle.
* @note   This example shows a simple way to report end of DMA2D transfer, and
*         you can add your own implementation.
* @retval None
*/
void DMA2D_TransferComplete(DMA2D_HandleTypeDef *hdma2d)
{

}

/**
* @brief  DMA2D error callbacks
* @param  hdma2d: DMA2D handle
* @note   This example shows a simple way to report DMA2D transfer error, and you can
*         add your own implementation.
* @retval None
*/
void DMA2D_TransferError(DMA2D_HandleTypeDef *hdma2d)
{

}
#endif

#if USE_LV_GPU != 0
/**
* @brief DMA2D configuration.
* @note  This function Configure the DMA2D peripheral :
*        1) Configure the Transfer mode as memory to memory with blending.
*        2) Configure the output color mode as RGB565 pixel format.
*        3) Configure the foreground
*          - first image loaded from FLASH memory
*          - constant alpha value (decreased to see the background)
*          - color mode as RGB565 pixel format
*        4) Configure the background
*          - second image loaded from FLASH memory
*          - color mode as RGB565 pixel format
* @retval None
*/
static void DMA2D_Config(void)
{
	/* Configure the DMA2D Mode, Color Mode and output offset */
	hdma2d_discovery.Init.Mode = DMA2D_M2M_BLEND;

#if LV_COLOR_DEPTH == 24
	hdma2d_discovery.Init.ColorMode = DMA2D_ARGB8888;
#elif LV_COLOR_DEPTH == 16
	hdma2d_discovery.Init.ColorMode = DMA2D_OUTPUT_RGB565;
#endif

	hdma2d_discovery.Init.OutputOffset = 0x0;

	/* DMA2D Callbacks Configuration */
	hdma2d_discovery.XferCpltCallback = DMA2D_TransferComplete;
	hdma2d_discovery.XferErrorCallback = DMA2D_TransferError;

	/* Foreground Configuration */
	hdma2d_discovery.LayerCfg[1].AlphaMode = DMA2D_REPLACE_ALPHA;
	hdma2d_discovery.LayerCfg[1].InputAlpha = 0xFF;

#if LV_COLOR_DEPTH == 24
	hdma2d_discovery.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
#elif LV_COLOR_DEPTH == 16
	hdma2d_discovery.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB565;
#endif

	hdma2d_discovery.LayerCfg[1].InputOffset = 0x0;

	/* Background Configuration */
	hdma2d_discovery.LayerCfg[0].AlphaMode = DMA2D_REPLACE_ALPHA;
	hdma2d_discovery.LayerCfg[0].InputAlpha = 0xFF;

#if LV_COLOR_DEPTH == 24
	hdma2d_discovery.LayerCfg[0].InputColorMode = DMA2D_INPUT_ARGB8888;
#elif LV_COLOR_DEPTH == 16
	hdma2d_discovery.LayerCfg[0].InputColorMode = DMA2D_INPUT_RGB565;
#endif

	hdma2d_discovery.LayerCfg[0].InputOffset = 0x0;

	hdma2d_discovery.Instance = DMA2D;

	/* DMA2D Initialization */
	if (HAL_DMA2D_Init(&hdma2d_discovery) != HAL_OK)
	{
		/* Initialization Error */
		//Error_Handler();
	}

	HAL_DMA2D_ConfigLayer(&hdma2d_discovery, 0);
	HAL_DMA2D_ConfigLayer(&hdma2d_discovery, 1);
}
#endif

/**********************
*   STATIC FUNCTIONS
**********************/

/**
* @brief  Fonction qui écrit (met à jour) une partie de l'écran. La librairie graphique décide de l'emplacement à mettre à jour
* @param x1 left coordinate of the rectangle
* @param x2 right coordinate of the rectangle
* @param y1 top coordinate of the rectangle
* @param y2 bottom coordinate of the rectangle
* @param color_p pointer to an array of colors
* @note   C'est une fonction qui vient d'un exemple du créateur de la librairie graphique
* @retval Rien
*/
static void tft_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p)
{
	/*Return if the area is out the screen*/
	if (x2 < 0) return;
	if (y2 < 0) return;
	if (x1 > TFT_HOR_RES - 1) return;
	if (y1 > TFT_VER_RES - 1) return;

	/*Truncate the area to the screen*/
	int32_t act_x1 = x1 < 0 ? 0 : x1;
	int32_t act_y1 = y1 < 0 ? 0 : y1;
	int32_t act_x2 = x2 > TFT_HOR_RES - 1 ? TFT_HOR_RES - 1 : x2;
	int32_t act_y2 = y2 > TFT_VER_RES - 1 ? TFT_VER_RES - 1 : y2;

	x1_flush = act_x1;
	y1_flush = act_y1;
	x2_flush = act_x2;
	y2_fill = act_y2;
	y_fill_act = act_y1;
	buf_to_flush = color_p;

	/*
	if((hdsi_discovery.Instance->WCR & 0b100) == 0) //p.727
	{
		HAL_StatusTypeDef err;
		err = HAL_DMA_Start_IT(DMA_M2M,(uint32_t)buf_to_flush, (uint32_t)&my_fb[y_fill_act * TFT_HOR_RES + x1_flush],
				  (x2_flush - x1_flush + 1));
		if(err != HAL_OK)
		{
			while(1);
		}
	}
	else  //L'écran est active et le DMA ne peut accèder à la SDRAM en même temps
	{

	}
	*/
	HAL_StatusTypeDef err;

#if LV_COLOR_DEPTH == 24
	err = HAL_DMA_Start_IT(DMA_M2M,
						  (uint32_t)buf_to_flush,
						  (uint32_t)&my_fb[y_fill_act * TFT_HOR_RES + x1_flush],  //Démarre le DMA
						  (x2_flush - x1_flush + 1));
#elif LV_COLOR_DEPTH == 16
	err = HAL_DMA_Start_IT(DMA_M2M,
							  (uint32_t)buf_to_flush,
							  (uint32_t)&my_fb[y_fill_act * TFT_HOR_RES + x1_flush],  //Démarre le DMA
							  (x2_flush - x1_flush + 1));
#endif

	if(err != HAL_OK)  //Si c'est une mauvaise config
	{
		while(1);	/*Halt on error*/
	}

	/*
	char buf[10];
	sprintf(buf, "%zu", my_fb);
	BSP_LCD_DisplayStringAtLine(750, buf);
	*/
}

/**
* @brief  Fonction qui écrit (met à jour) une partie rectangle de l'écran. La librairie graphique décide de l'emplacement à mettre à jour
* @param x1 left coordinate of the rectangle
* @param x2 right coordinate of the rectangle
* @param y1 top coordinate of the rectangle
* @param y2 bottom coordinate of the rectangle
* @param color fill color
* @note   C'est une fonction qui vient d'un exemple du créateur de la librairie graphique
* @retval Rien
*/
static void tft_fill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color)
{
	/*Return if the area is out the screen*/
	if (x2 < 0) return;
	if (y2 < 0) return;
	if (x1 > TFT_HOR_RES - 1) return;
	if (y1 > TFT_VER_RES - 1) return;

	/*Truncate the area to the screen*/
	int32_t act_x1 = x1 < 0 ? 0 : x1;
	int32_t act_y1 = y1 < 0 ? 0 : y1;
	int32_t act_x2 = x2 > TFT_HOR_RES - 1 ? TFT_HOR_RES - 1 : x2;
	int32_t act_y2 = y2 > TFT_VER_RES - 1 ? TFT_VER_RES - 1 : y2;

	uint32_t x;
	uint32_t y;

	/*Fill the remaining area*/
	for (x = act_x1; x <= act_x2; x++) {
		for (y = act_y1; y <= act_y2; y++) {
			my_fb[y * TFT_HOR_RES + x] = color.full;  //Écrit directement dans le buffer de la SDRAM
		}
	}
}


/**
* @brief  Fonction qui écrit (met à jour) la couleur d'une partie rectangle de l'écran. La librairie graphique décide de l'emplacement à mettre à jour
* @param x1 left coordinate of the rectangle
* @param x2 right coordinate of the rectangle
* @param y1 top coordinate of the rectangle
* @param y2 bottom coordinate of the rectangle
* @param color_p pointer to an array of colors
* @note   C'est une fonction qui vient d'un exemple du créateur de la librairie graphique
* @retval Rien
*/
static void tft_map(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p)
{
	/*Return if the area is out the screen*/
	if (x2 < 0) return;
	if (y2 < 0) return;
	if (x1 > TFT_HOR_RES - 1) return;
	if (y1 > TFT_VER_RES - 1) return;

	/*Truncate the area to the screen*/
	int32_t act_x1 = x1 < 0 ? 0 : x1;
	int32_t act_y1 = y1 < 0 ? 0 : y1;
	int32_t act_x2 = x2 > TFT_HOR_RES - 1 ? TFT_HOR_RES - 1 : x2;
	int32_t act_y2 = y2 > TFT_VER_RES - 1 ? TFT_VER_RES - 1 : y2;

#if LV_VDB_DOUBLE == 0
	uint32_t y;
	for (y = act_y1; y <= act_y2; y++) {
		memcpy((void*)&my_fb[y * TFT_HOR_RES + act_x1],
			color_p,
			(act_x2 - act_x1 + 1) * sizeof(my_fb[0]));
		color_p += x2 - x1 + 1;    /*Skip the parts out of the screen*/
	}
#else

	x1_flush = act_x1;
	y1_flush = act_y1;
	x2_flush = act_x2;
	y2_fill = act_y2;
	y_fill_act = act_y1;
	buf_to_flush = color_p;

	/*
	if (BSP_SDRAM_WriteData_DMA((uint32_t)&my_fb[y_fill_act * TFT_HOR_RES + x1_flush], (uint32_t*)buf_to_flush, (x2_flush - x1_flush + 1)))
	{
		while (1);
	}
	*/
	HAL_StatusTypeDef err;

#if LV_COLOR_DEPTH == 24   //Démarre le DMA
	err = HAL_DMA_Start_IT(DMA_M2M,
							  (uint32_t)buf_to_flush,
							  (uint32_t)&my_fb[y_fill_act * TFT_HOR_RES + x1_flush],
							  (x2_flush - x1_flush + 1));
#elif LV_COLOR_DEPTH == 16
	err = HAL_DMA_Start_IT(DMA_M2M,
							  (uint32_t)buf_to_flush,
							  (uint32_t)&my_fb[y_fill_act * TFT_HOR_RES + x1_flush],  //Démarre le DMA
							  (x2_flush - x1_flush + 1));
#endif

	if(err != HAL_OK)
	{
		while(1);	/*Halt on error*/
	}

#endif
}


#if USE_LV_GPU != 0
/**
* @brief  Fonction qui utilise le DMA2D pour calculer la transparence de certains pixels de la SDRAM vers la SDRAM
* @param dest a memory address. Copy 'src' here.
* @param src pointer to pixel map. Copy it to 'dest'.
* @param length number of pixels in 'src'
* @param opa opacity (0, OPA_TRANSP: transparent ... 255, OPA_COVER, fully cover)
* @note   C'est une fonction qui vient d'un exemple du créateur de la librairie graphique
* @retval Rien
*/
static void gpu_mem_blend(lv_color_t * dest, const lv_color_t * src, uint32_t length, lv_opa_t opa)
{
	/*Wait for the previous operation*/
	HAL_DMA2D_PollForTransfer(&hdma2d_discovery, 10);
	hdma2d_discovery.Init.Mode = DMA2D_M2M_BLEND;
	/* DMA2D Initialization */
	if (HAL_DMA2D_Init(&hdma2d_discovery) != HAL_OK)
	{
		/* Initialization Error */
		while (1);
	}

	hdma2d_discovery.LayerCfg[1].InputAlpha = opa;
	HAL_DMA2D_ConfigLayer(&hdma2d_discovery, 1);

#if LV_COLOR_DEPTH == 24
	HAL_DMA2D_BlendingStart(&hdma2d_discovery,
							   (uint32_t)src,
							   (uint32_t)dest,
							   (uint32_t)dest,
							   length,
							   1);  //Démarre le DMA2D
#elif LV_COLOR_DEPTH == 16
	HAL_DMA2D_BlendingStart(&hdma2d_discovery,
							   (uint32_t)src,
							   (uint32_t)dest,
							   (uint32_t)dest,
							   length,
							   1);  //Démarre le DMA2D
#endif
}

/**
* @brief  Fonction qui utilise le DMA2D pour calculer la transparence de certains pixels de la librairie vers la SDRAM
* @param dest a memory address. Copy 'src' here.
* @param src pointer to pixel map. Copy it to 'dest'.
* @param length number of pixels in 'src'
* @param opa opacity (0, OPA_TRANSP: transparent ... 255, OPA_COVER, fully cover)
* @note   C'est une fonction qui vient d'un exemple du créateur de la librairie graphique
* @retval Rien
*/
static void gpu_mem_fill(lv_color_t * dest, uint32_t length, lv_color_t color)
{
	/*Wait for the previous operation*/
	HAL_DMA2D_PollForTransfer(&hdma2d_discovery, 10);

	hdma2d_discovery.Init.Mode = DMA2D_R2M;
	/* DMA2D Initialization */
	if (HAL_DMA2D_Init(&hdma2d_discovery) != HAL_OK)
	{
		/* Initialization Error */
		while (1);
	}

	hdma2d_discovery.LayerCfg[1].InputAlpha = 0xff;
	HAL_DMA2D_ConfigLayer(&hdma2d_discovery, 1);

#if LV_COLOR_DEPTH == 24
	HAL_DMA2D_BlendingStart(&hdma2d_discovery,
							   (uint32_t)lv_color_to24(color),
							   (uint32_t)dest,
							   (uint32_t)dest,
							   length,
							   1);
#elif LV_COLOR_DEPTH == 16
	HAL_DMA2D_BlendingStart(&hdma2d_discovery,
							   (uint32_t)lv_color_to24(color),
							   (uint32_t)dest,
							   (uint32_t)dest,
							   length,
							   1);
#endif
}

#endif

/**
* @brief  Fonction qui lit les coordonnés de l'écran tactile et l'integre dans la librairie
* @param indev_id id of the input device to read
* @param x put the x coordinate here
* @param y put the y coordinate here
* @note   C'est une fonction qui vient d'un exemple du créateur de la librairie graphique
* @retval Rien
*/
static bool touchpad_read(lv_indev_data_t *data)
{
	static int16_t last_x = 0;
	static int16_t last_y = 0;

	BSP_TS_GetState(&TS_State);
	if(TS_State.touchDetected != 0) {
		data->point.x = TS_State.touchY[0] -80;
		data->point.y = 400-TS_State.touchX[0];
		last_x = data->point.x;
		last_y = data->point.y;
		data->state = LV_INDEV_STATE_PR;
	} else {
		data->point.x = last_x;
		data->point.y = last_y;
		data->state = LV_INDEV_STATE_REL;
	}

	return false; /*false: no more data to read because we are no buffering*/
}


/**
* @brief  Callback si le transfert DMA est complété.
* @note   Cette fonction est exécutée lorsque l'interruption de fin de transfert est levée.
* @retval Aucune
*/
void DMA_TransferComplete(DMA_HandleTypeDef *hdma)
{
	y_fill_act++;

	if (y_fill_act > y2_fill) {
		lv_flush_ready();
		//hdsi_discovery.Instance->WCR |= 0b100;
	}
	else
	{
		buf_to_flush += x2_flush - x1_flush + 1;
		/*##-7- Start the DMA transfer using the interrupt mode ####################*/
		/* Configure the source, destination and buffer size DMA fields and Start DMA Stream transfer */
		/* Enable All the DMA interrupts */

#if LV_COLOR_DEPTH == 24
		if  (HAL_DMA_Start_IT(hdma, (uint32_t)buf_to_flush, (uint32_t)&my_fb[y_fill_act * TFT_HOR_RES + x1_flush], (x2_flush - x1_flush + 1)) != HAL_OK)
		{
			while (1);	/*Halt on error*/
		}
#elif LV_COLOR_DEPTH == 16
		if (HAL_DMA_Start_IT(hdma, (uint32_t)buf_to_flush, (uint32_t)&my_fb[y_fill_act * TFT_HOR_RES + x1_flush], (x2_flush - x1_flush + 1)) != HAL_OK)
		{
			while (1);	/*Halt on error*/
		}
#endif

	}
}

/**
* @brief  DMA conversion error callback
* @note   This function is executed when the transfer error interrupt
*         is generated during DMA transfer
* @retval None
*/
void DMA_TransferError(DMA_HandleTypeDef *hdma)
{

}

/**
  * @brief  Interrupt callback du ldtc. Après configuration, un interrupt est généré par la synchronisation verticale de l'écran. C'est ce qui gère le double buffering.
  * 		La fonction n'est pas utilisée, car la librairie n'écrit que sur une partie de l'écran. Ainsi, les deux buffers ne contiennent pas les mêmes données et du stuttering
  * 		se fait sur l'écran.
  * @param  hltdc: Pointeur vers une structure LTDC_HandleTypeDef qui contient la configuration pour le LTDC.
  * @retval Aucune
  */
void HAL_LTDC_LineEventCallback(LTDC_HandleTypeDef *hltdc)
{
	/*
	if(my_fb == 0xD0000000)  //((LTDC_LAYER(hltdc, 0)->CFBAR) == 0xC0000000)
	{
		//LTDC_LAYER(hltdc, 0)->CFBAR &= ~(LTDC_LxCFBAR_CFBADD);
		LTDC_LAYER(hltdc, 0)->CFBAR = (0xD0000000);
		my_fb = (__IO uint32_t*) 0xC0000000;
	}
	else
	{
		//LTDC_LAYER(hltdc, 0)->CFBAR &= ~(LTDC_LxCFBAR_CFBADD);
		LTDC_LAYER(hltdc, 0)->CFBAR = (0xC0000000);
		my_fb = (__IO uint32_t*) 0xD0000000;
	}
	//LTDC->SRCR = LTDC_SRCR_VBR;   //Reload sur un vertical sync
	//__HAL_LTDC_RELOAD_CONFIG(hltdc);  //Semble reloader la configuration sur le champ

	HAL_LTDC_ProgramLineEvent(hltdc, 0);
	//my_fb = (__IO uint32_t) BSP_LCD_SwapBuffer();
	 */
}
