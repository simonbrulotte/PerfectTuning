/*
 * ledDriver.h
 *
 *  Created on: 13 avr. 2018
 *      Author: TophersAlien
 */

#ifndef LEDDRIVER_H_
#define LEDDRIVER_H_

#include <PixelArray.hpp>
#include <WS2812.hpp>
#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

void ledDriver_init();
void ledDriver_refreshColor();

#define ARD_D8_Pin GPIO_PIN_4  //Define qui vient du main.h généré par le cubeMX


#endif /* LEDDRIVER_H_ */
