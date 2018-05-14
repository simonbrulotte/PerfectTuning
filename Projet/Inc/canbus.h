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
HAL_StatusTypeDef canbusWrite(uint8_t *data, uint8_t dataLenght);
void canbusPollingTest();


#endif /* CANBUS_H_ */
