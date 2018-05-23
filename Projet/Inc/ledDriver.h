/*
 * ledDriver.h
 *
 *  Created on: 1 mai 2018
 *      Author: TophersAlien
 */

#ifndef LEDDRIVER_H_
#define LEDDRIVER_H_


//extern TIM_HandleTypeDef htim4;  //Variable intialisée comme externe dans le fichier tim.h du code exemple, mais je ne vois l'utilité de l'avoir jusqu'à maintenant

//vient de ws2812_handler.h
#define N_LEDS 48  //24 //(72)
#define H_VAL 70//65//33
#define L_VAL 35//32//16
#define TOTAL_VAL 67  //Periode
#define BITS_PER_LED ((3*8))  //*3)  //8 bits par couleur * 3 (RGB) * 3 (H_VAL + L_VAL, NbPulse, H_VAL | L_VAL)
#define BIT_BUF_SIZE ((N_LEDS * (BITS_PER_LED)))// + 5)

typedef struct{
	uint16_t nbDel;

	uint8_t valR;
	uint8_t valG;
	uint8_t valB;
}delStruct;

delStruct m_cad1, m_cad2, m_cad3, m_cad4;

//void initLedBar();
void ledDriver_init();
void ws2812_set_color( int ledIdx, uint8_t r, uint8_t g, uint8_t b );
void lightLedBar();
void turnOffBar();
void ledDriverLogique();

void ledRingSplited(delStruct cad1, delStruct cad2, delStruct cad3, delStruct cad4, uint8_t nbCadran);

#endif /* LEDDRIVER_H_ */
