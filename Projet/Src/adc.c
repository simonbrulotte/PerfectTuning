/*
 * adc.c
 *
 *  Created on: May 22, 2018
 *      Author: TophersMSI
 */

/*------------------- Includes -------------------*/
#include <stdbool.h>
#include "adc.h"
#include "canbus.h"
#include "ledDriver.h"

/*------------------- Prototypes -------------------*/
extern void afficheGraphData_CanBus(uint32_t graphPointY);

/*------------------- Variables globales -------------------*/
ADC_HandleTypeDef hadc1;
uint8_t boucleAdcLogique=0;
extern ADC_HandleTypeDef hadc1;
extern bool can_mode_master;
extern bool led_flag;

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

void adcLogiqueAffichage(){
	if(boucleAdcLogique>=20){  //20 == 100ms
		if(can_mode_master == true){
			HAL_ADC_Start_IT(&hadc1);
		}
		boucleAdcLogique=0;
	}else
		boucleAdcLogique++;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	uint32_t valeurADC = HAL_ADC_GetValue(hadc);

	if(can_mode_master == true){
		uint8_t data[2] = {(valeurADC & 0xFF), (valeurADC & 0xF00)>>8};
		canbusWrite(CANBUS_ID_TYPE_GRAPH_DATA, data, sizeof(data));
	}
	afficheGraphData_CanBus(valeurADC);

	m_cad1.nbDel = (m_cad1.nbDel >= 6) ? 0 : m_cad1.nbDel + 1;
	m_cad2.nbDel = (m_cad2.nbDel >= 6) ? 0 : m_cad2.nbDel + 1;
	m_cad3.nbDel = (m_cad3.nbDel >= 6) ? 0 : m_cad3.nbDel + 1;
	m_cad4.nbDel = (m_cad4.nbDel >= 6) ? 0 : m_cad4.nbDel + 1;

	led_flag = true;
}
