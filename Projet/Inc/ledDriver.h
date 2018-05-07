/*
 * ledDriver.h
 *
 *  Created on: 1 mai 2018
 *      Author: TophersAlien
 */

#ifndef LEDDRIVER_H_
#define LEDDRIVER_H_


//extern TIM_HandleTypeDef htim4;  //Variable intialis�e comme externe dans le fichier tim.h du code exemple, mais je ne vois l'utilit� de l'avoir jusqu'� maintenant

//vient de ws2812_handler.h
#define N_LEDS (47)
#define H_VAL 70
#define L_VAL 35
#define BITS_PER_LED (3*8)
#define BIT_BUF_SIZE ((N_LEDS * (BITS_PER_LED)))// + 5)

//void initLedBar();
void ledDriver_init();
void ws2812_set_color( int ledIdx, uint8_t r, uint8_t g, uint8_t b );
void lightLedBar();
void turnOffBar();


#endif /* LEDDRIVER_H_ */
