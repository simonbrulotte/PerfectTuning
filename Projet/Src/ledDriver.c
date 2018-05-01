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

/* Defines  ------------------------------------------------------------------*/
#define H_VAL 70
#define L_VAL 35
#define BITS_PER_LED (3*8)
#define BIT_BUF_SIZE ((N_LEDS * BITS_PER_LED) + 5)

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim4;
DMA_HandleTypeDef hdma_tim4_ch1;  //*Variable fournie dans le code exemple, mais n'est pas utilisée dans ce dernier

uint32_t ws2812BitBuf[BIT_BUF_SIZE];  //Code du fichier ws2812_handler.c

/* Private function prototypes -----------------------------------------------*/
static void MX_TIM4_Init(void);
void MX_DMA_Init(void);


void ledDriver_init()
{
	MX_TIM4_Init();  //Timer pour la générationdu signal PWM de DELs
	MX_DMA_Init();   //L'instance DMA qui s'occupe de transférer les données pour le timer (unload le CPU)


}

/* tim4 init function */
void MX_TIM4_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 104;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_ENABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim4);
}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(timHandle->Instance==TIM4)
  {
  /* USER CODE BEGIN tim4_MspPostInit 0 */

  /* USER CODE END tim4_MspPostInit 0 */

    /**tim4 GPIO Configuration
    PA0-WKUP     ------> tim4_CH1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN tim4_MspPostInit 1 */

  /* USER CODE END tim4_MspPostInit 1 */
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
  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);

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

	/*
	 * while(mask > 0)
	 * {
	 * 		if(mask & g == 1)
	 *			ws2812BitBuf[i] = H_VAL;
	 *
	 * 		else
	 * 			ws2812BitBuf[i] = L_VAL;
	 *
	 * 		mask = mask >> 1;
	 *	 	i++;
	 *
	 * }
	 */
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
	HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_1, (uint32_t*) ws2812BitBuf,
			sizeof(ws2812BitBuf) / sizeof(ws2812BitBuf[0]));
}

