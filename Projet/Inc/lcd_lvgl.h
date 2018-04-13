/**
 * Fichier lcd_lvgl.h du projet qui contient les fonctions de son fichier .c . Les variables ne sont plus utilisées sauf SDRAM_BANK_ADDR, puisque c'est le pointeur où
 * le buffer d'écran est mit en mémoire.
 *
 * @Christopher Bullock-D'Arcy
 * @version 1.0
 * @Date 19 mars 2018
 */

#ifndef LCD_LVGL
#define LCD_LVGL

/*********************
*      INCLUDES
*********************/
#include <stdint.h>
#include "../lvgl/lv_misc/lv_color.h"
#include "../lvgl/lv_misc/lv_area.h"
#include "stm32f7xx_hal.h"

/*********************
*      DEFINES
*********************/
#define TFT_HOR_RES 480
#define TFT_VER_RES 800

#define TFT_EXT_FB		1		/*Frame buffer is located into an external SDRAM*/
#define TFT_USE_GPU		1		/*Enable hardware accelerator*/

#if TFT_EXT_FB != 0
#define SDRAM_BANK_ADDR     ((uint32_t)0xC0000000)  //Addresse de la banque numéro 2 de la SDRAM
#endif

/**********************
*      TYPEDEFS
**********************/

/**********************
* GLOBAL PROTOTYPES
**********************/
void lvgl_init(DMA_HandleTypeDef *dma_handle, DMA2D_HandleTypeDef *dma2d_handle);  //Fonction d'initialisation de notre driver graphique

extern void DMA_TransferError(DMA_HandleTypeDef *hdma);  //Les callbacks liés à l'interrupt du DMA
extern void DMA_TransferComplete(DMA_HandleTypeDef *hdma);

extern void DMA2D_TransferComplete(DMA2D_HandleTypeDef *hdma2d); //Les callbacks liés à l'interrupt du DMA2D
extern void DMA2D_TransferError(DMA2D_HandleTypeDef *hdma2d);

extern DSI_HandleTypeDef hdsi_discovery;  //TypeDef pour la configuration du module DSI

/**********************
*      MACROS
**********************/

#endif
