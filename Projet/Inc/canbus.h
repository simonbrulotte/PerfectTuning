/*
 * canbus.h
 *
 *  Created on: 14 mai 2018
 *      Author: TophersMSI
 */

#ifndef CANBUS_H_
#define CANBUS_H_

#include "main.h"
#include "Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery.h"

void canbusInit();
HAL_StatusTypeDef CAN_Polling(void);
void canbusReceive();
void canbusPollingTest();
HAL_StatusTypeDef canbusWrite(uint32_t idDataType, uint8_t *data, uint8_t dataLenght);

extern void afficheCanBus_Data(uint8_t *data, uint8_t dataLenght);
void canbusLogiqueAffichage();

enum{
	CANBUS_ID_TYPE_LED_DATA = 0,
	CANBUS_ID_TYPE_GAUGE_DATA,
	CANBUS_ID_TYPE_MESSAGE,
	CANBUS_ID_TYPE_GRAPH_DATA
};

#endif /* CANBUS_H_ */
