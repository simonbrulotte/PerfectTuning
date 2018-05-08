/*
 * ledDriver.c
 *
 *  Created on: 1 mai 2018
 *      Author: TophersAlien
 */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "stm32f7xx_hal.h"
#include "ledDriver.h"
#include "main.h"

/* Defines  ------------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;
DMA_HandleTypeDef hdma_tim3_ch3;  //*Variable fournie dans le code exemple, mais n'est pas utilis�e dans ce dernier

uint32_t ws2812BitBuf[BIT_BUF_SIZE];  //Code du fichier ws2812_handler.c

/* Private function prototypes -----------------------------------------------*/
static void MX_TIM3_Init(void);
void MX_DMA_Init(void);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle);
void initLedBar();


void ledDriver_init()
{
	MX_DMA_Init();   //L'instance DMA qui s'occupe de transf�rer les donn�es pour le timer (unload le CPU)
	MX_TIM3_Init();  //Timer pour la g�n�rationdu signal PWM de DELs

	initLedBar();
}

/* tim3 init function */
void MX_TIM3_Init(void)
{
	/*
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 104;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_ENABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim3);
  */

  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 67; // Click ABP1 54MHz
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
	_Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
	_Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 10;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_ENABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
	_Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim3);
  //HAL_TIM_PWM_MspInit(&htim3);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_pwm)
{

  if(htim_pwm->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();

    /* TIM3 DMA Init */
    /* TIM3_CH3 Init */
    hdma_tim3_ch3.Instance = DMA1_Stream7;
    hdma_tim3_ch3.Init.Channel = DMA_CHANNEL_5;
    hdma_tim3_ch3.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_tim3_ch3.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_tim3_ch3.Init.MemInc = DMA_MINC_ENABLE;
    hdma_tim3_ch3.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_tim3_ch3.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_tim3_ch3.Init.Mode = DMA_NORMAL;
//    hdma_tim3_ch3.Init.MemBurst = DMA_MBURST_SINGLE;
    hdma_tim3_ch3.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_tim3_ch3.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_tim3_ch3) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    __HAL_LINKDMA(htim_pwm,hdma[TIM_DMA_ID_CC3],hdma_tim3_ch3);

    /* TIM3 interrupt Init */
    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspInit 1 */

  /* USER CODE END TIM3_MspInit 1 */
  }

}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{
	/*
  GPIO_InitTypeDef GPIO_InitStruct;

  if(timHandle->Instance==TIM3)
  {
	__HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitStruct.Pin = ARD_D5_PWM_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  }
  */
  GPIO_InitTypeDef GPIO_InitStruct;
  if(timHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspPostInit 0 */
	__HAL_RCC_GPIOC_CLK_ENABLE();
  /* USER CODE END TIM3_MspPostInit 0 */

	/**TIM3 GPIO Configuration
	PC8     ------> TIM3_CH3
	*/
	GPIO_InitStruct.Pin = ARD_D5_PWM_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
	HAL_GPIO_Init(ARD_D5_PWM_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM3_MspPostInit 1 */

  /* USER CODE END TIM3_MspPostInit 1 */
  }
}

/**
  * Enable DMA controller clock
  */
void MX_DMA_Init(void)
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream7_IRQn);
}


void initLedBar()
{
	for (int i = 0; i < BIT_BUF_SIZE; i++)
		ws2812BitBuf[i] = 0;

	turnOffBar();
}

void turnOffBar()
{
	for (int i = 0; i < N_LEDS; i++)
		ws2812_set_color(i, 0, 0, 0);

	lightLedBar();
}

void ws2812_set_color(int ledIdx, uint8_t r, uint8_t g, uint8_t b)
{
	if (ledIdx >= N_LEDS)
		return;

	int i = ledIdx * BITS_PER_LED;
	uint8_t mask;
	mask = 0x80;
	while (mask)
	{
		ws2812BitBuf[i] = (mask & g) ? H_VAL : L_VAL;
		mask >>= 1;
		i++;
	}

	mask = 0x80;
	while (mask)
	{
		ws2812BitBuf[i] = (mask & r) ? H_VAL : L_VAL;
		mask >>= 1;
		i++;
	}
	mask = 0x80;
	while (mask)
	{
		ws2812BitBuf[i] = (mask & b) ? H_VAL : L_VAL;
		mask >>= 1;
		i++;
	}



}

void lightLedBar()
{
	HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_3, (uint32_t*) ws2812BitBuf, sizeof(ws2812BitBuf) / sizeof(ws2812BitBuf[0]));
	//HAL_GPIO_TogglePin(ARD_D5_PWM_GPIO_Port, ARD_D5_PWM_Pin);
}

