/*
 * WS2812.h
 *
 *  Created on: 18 avr. 2018
 *      Author: TophersAlien
 */

#ifndef WS2812_H_
#define WS2812_H_

#include "stdbool.h"
#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"
#include "main.h"

#define FRAME_SIZE 24

enum BrightnessControl { OFF, GLOBAL, PER_PIXEL };

void initWS2812(int pin, GPIO_TypeDef *port, int zeroHigh, int zeroLow, int oneHigh, int oneLow);
void setDelays(int zeroHigh, int zeroLow, int oneHigh, int oneLow);
void write_offsets(int buf[], int r_offset, int g_offset, int b_offset);
void write(int buf[]);
void useII(enum BrightnessControl bc);
void setII(unsigned char II);


#endif /* WS2812_H_ */
