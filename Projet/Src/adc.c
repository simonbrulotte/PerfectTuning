/*
 * adc.c
 *
 *  Created on: May 22, 2018
 *      Author: TophersMSI
 */

/*------------------- Includes -------------------*/
#include "adc.h"

/*------------------- Variables globales -------------------*/
extern void afficheGraphData_CanBus(uint32_t graphPointY);

/*------------------- Variables globales -------------------*/
ADC_HandleTypeDef hadc1;

void initADC()
{
  ADC_ChannelConfTypeDef sConfig;

	/**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	*/
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
	_Error_Handler(__FILE__, __LINE__);
  }

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	*/
  sConfig.Channel = ADC_CHANNEL_12;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
	_Error_Handler(__FILE__, __LINE__);
  }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	afficheGraphData_CanBus(HAL_ADC_GetValue(hadc));
}
