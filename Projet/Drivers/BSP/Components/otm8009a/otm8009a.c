/**
  ******************************************************************************
  * @file    otm8009a.c
  * @author  MCD Application Team
  * @brief   This file provides the LCD Driver for KoD KM-040TMP-02-0621 (WVGA)
  *          DSI LCD Display OTM8009A.   
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "otm8009a.h"

/** @addtogroup BSP
  * @{
  */
  
/** @addtogroup Components
  * @{
  */ 

/** @defgroup OTM8009A OTM8009A
  * @brief     This file provides a set of functions needed to drive the 
  *            otm8009a IC display driver.
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup OTM8009A_Private_Constants OTM8009A Private Constants
  * @{
  */

/*
 * @brief Constant tables of register settings used to transmit DSI
 * command packets as power up initialization sequence of the KoD LCD (OTM8009A LCD Driver)
 */
const uint8_t lcdRegData1[]  = {0x80,0x09,0x01,0xFF};
const uint8_t lcdRegData2[]  = {0x80,0x09,0xFF};
const uint8_t lcdRegData3[]  = {0x00,0x09,0x0F,0x0E,0x07,0x10,0x0B,0x0A,0x04,0x07,0x0B,0x08,0x0F,0x10,0x0A,0x01,0xE1};
const uint8_t lcdRegData4[]  = {0x00,0x09,0x0F,0x0E,0x07,0x10,0x0B,0x0A,0x04,0x07,0x0B,0x08,0x0F,0x10,0x0A,0x01,0xE2};
const uint8_t lcdRegData5[]  = {0x79,0x79,0xD8};
const uint8_t lcdRegData6[]  = {0x00,0x01,0xB3};
const uint8_t lcdRegData7[]  = {0x85,0x01,0x00,0x84,0x01,0x00,0xCE};
const uint8_t lcdRegData8[]  = {0x18,0x04,0x03,0x39,0x00,0x00,0x00,0x18,0x03,0x03,0x3A,0x00,0x00,0x00,0xCE};
const uint8_t lcdRegData9[]  = {0x18,0x02,0x03,0x3B,0x00,0x00,0x00,0x18,0x01,0x03,0x3C,0x00,0x00,0x00,0xCE};
const uint8_t lcdRegData10[] = {0x01,0x01,0x20,0x20,0x00,0x00,0x01,0x02,0x00,0x00,0xCF};
const uint8_t lcdRegData11[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCB};
const uint8_t lcdRegData12[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCB};
const uint8_t lcdRegData13[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCB};
const uint8_t lcdRegData14[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCB};
const uint8_t lcdRegData15[] = {0x00,0x04,0x04,0x04,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCB};
const uint8_t lcdRegData16[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0x04,0x04,0x04,0x00,0x00,0x00,0x00,0xCB};
const uint8_t lcdRegData17[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCB};
const uint8_t lcdRegData18[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xCB};
const uint8_t lcdRegData19[] = {0x00,0x26,0x09,0x0B,0x01,0x25,0x00,0x00,0x00,0x00,0xCC};
const uint8_t lcdRegData20[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x26,0x0A,0x0C,0x02,0xCC};
const uint8_t lcdRegData21[] = {0x25,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC};
const uint8_t lcdRegData22[] = {0x00,0x25,0x0C,0x0A,0x02,0x26,0x00,0x00,0x00,0x00,0xCC};
const uint8_t lcdRegData23[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x25,0x0B,0x09,0x01,0xCC};
const uint8_t lcdRegData24[] = {0x26,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC};
const uint8_t lcdRegData25[] = {0xFF,0xFF,0xFF,0xFF};    
/*
  * CASET value (Column Address Set) : X direction LCD GRAM boundaries
  * depending on LCD orientation mode and PASET value (Page Address Set) : Y direction
  * LCD GRAM boundaries depending on LCD orientation mode
  * XS[15:0] = 0x000 = 0, XE[15:0] = 0x31F = 799 for landscape mode : apply to CASET
  * YS[15:0] = 0x000 = 0, YE[15:0] = 0x31F = 799 for portrait mode : : apply to PASET
  */
const uint8_t lcdRegData27[] = {0x00, 0x00, 0x03, 0x1F, OTM8009A_CMD_CASET};
/*
  * XS[15:0] = 0x000 = 0, XE[15:0] = 0x1DF = 479 for portrait mode : apply to CASET
  * YS[15:0] = 0x000 = 0, YE[15:0] = 0x1DF = 479 for landscape mode : apply to PASET
 */
const uint8_t lcdRegData28[] = {0x00, 0x00, 0x01, 0xDF, OTM8009A_CMD_PASET};


const uint8_t ShortRegData1[]  = {OTM8009A_CMD_NOP, 0x00};
const uint8_t ShortRegData2[]  = {OTM8009A_CMD_NOP, 0x80};
const uint8_t ShortRegData3[]  = {0xC4, 0x30};
const uint8_t ShortRegData4[]  = {OTM8009A_CMD_NOP, 0x8A};
const uint8_t ShortRegData5[]  = {0xC4, 0x40};
const uint8_t ShortRegData6[]  = {OTM8009A_CMD_NOP, 0xB1};
const uint8_t ShortRegData7[]  = {0xC5, 0xA9};
const uint8_t ShortRegData8[]  = {OTM8009A_CMD_NOP, 0x91};
const uint8_t ShortRegData9[]  = {0xC5, 0x34};
const uint8_t ShortRegData10[] = {OTM8009A_CMD_NOP, 0xB4};
const uint8_t ShortRegData11[] = {0xC0, 0x50};
const uint8_t ShortRegData12[] = {0xD9, 0x4E};
const uint8_t ShortRegData13[] = {OTM8009A_CMD_NOP, 0x81};
const uint8_t ShortRegData14[] = {0xC1, 0x66};
const uint8_t ShortRegData15[] = {OTM8009A_CMD_NOP, 0xA1};
const uint8_t ShortRegData16[] = {0xC1, 0x08};
const uint8_t ShortRegData17[] = {OTM8009A_CMD_NOP, 0x92};
const uint8_t ShortRegData18[] = {0xC5, 0x01};
const uint8_t ShortRegData19[] = {OTM8009A_CMD_NOP, 0x95};
const uint8_t ShortRegData20[] = {OTM8009A_CMD_NOP, 0x94};
const uint8_t ShortRegData21[] = {0xC5, 0x33};
const uint8_t ShortRegData22[] = {OTM8009A_CMD_NOP, 0xA3};
const uint8_t ShortRegData23[] = {0xC0, 0x1B};
const uint8_t ShortRegData24[] = {OTM8009A_CMD_NOP, 0x82};
const uint8_t ShortRegData25[] = {0xC5, 0x83};
const uint8_t ShortRegData26[] = {0xC4, 0x83};
const uint8_t ShortRegData27[] = {0xC1, 0x0E};
const uint8_t ShortRegData28[] = {OTM8009A_CMD_NOP, 0xA6};
const uint8_t ShortRegData29[] = {OTM8009A_CMD_NOP, 0xA0};
const uint8_t ShortRegData30[] = {OTM8009A_CMD_NOP, 0xB0};
const uint8_t ShortRegData31[] = {OTM8009A_CMD_NOP, 0xC0};
const uint8_t ShortRegData32[] = {OTM8009A_CMD_NOP, 0xD0};
const uint8_t ShortRegData33[] = {OTM8009A_CMD_NOP, 0x90};
const uint8_t ShortRegData34[] = {OTM8009A_CMD_NOP, 0xE0};
const uint8_t ShortRegData35[] = {OTM8009A_CMD_NOP, 0xF0};
const uint8_t ShortRegData36[] = {OTM8009A_CMD_SLPOUT, 0x00};
const uint8_t ShortRegData37[] = {OTM8009A_CMD_COLMOD, OTM8009A_COLMOD_RGB565};
const uint8_t ShortRegData38[] = {OTM8009A_CMD_COLMOD, OTM8009A_COLMOD_RGB888};
const uint8_t ShortRegData39[] = {OTM8009A_CMD_MADCTR, OTM8009A_MADCTR_MODE_LANDSCAPE};
const uint8_t ShortRegData40[] = {OTM8009A_CMD_WRDISBV, 0x7F};
const uint8_t ShortRegData41[] = {OTM8009A_CMD_WRCTRLD, 0x2C};
const uint8_t ShortRegData42[] = {OTM8009A_CMD_WRCABC, 0x02};
const uint8_t ShortRegData43[] = {OTM8009A_CMD_WRCABCMB, 0xFF};
const uint8_t ShortRegData44[] = {OTM8009A_CMD_DISPON, 0x00};
const uint8_t ShortRegData45[] = {OTM8009A_CMD_RAMWR, 0x00};
const uint8_t ShortRegData46[] = {0xCF, 0x00};
const uint8_t ShortRegData47[] = {0xC5, 0x66};
const uint8_t ShortRegData48[] = {OTM8009A_CMD_NOP, 0xB6};
const uint8_t ShortRegData49[] = {0xF5, 0x06};
const uint8_t ShortRegData50[] = {OTM8009A_CMD_NOP, 0xB1};
const uint8_t ShortRegData51[] = {0xC6, 0x06};
/**
  * @}
  */

const uint8_t OledShortRegData1[] = {0xFE,0x04};
const uint8_t OledShortRegData2[] = {0x00,0xdc};
const uint8_t OledShortRegData3[] = {0x01,0x00};
const uint8_t OledShortRegData4[] = {0x02,0x02};
const uint8_t OledShortRegData5[] = {0x03,0x00};
const uint8_t OledShortRegData6[] = {0x04,0x00};
const uint8_t OledShortRegData7[] = {0x05,0x03};
const uint8_t OledShortRegData8[] = {0x06,0x16};
const uint8_t OledShortRegData9[] = {0x07,0x13};
const uint8_t OledShortRegData10[] = {0x08,0x08};
const uint8_t OledShortRegData11[] = {0x09,0xdc};
const uint8_t OledShortRegData12[] = {0x0a,0x00};
const uint8_t OledShortRegData13[] = {0x0b,0x02};
const uint8_t OledShortRegData14[] = {0x0c,0x00};
const uint8_t OledShortRegData15[] = {0x0d,0x00};
const uint8_t OledShortRegData16[] = {0x0e,0x02};
const uint8_t OledShortRegData17[] = {0x0f,0x16};
const uint8_t OledShortRegData18[] = {0x10,0x18};
const uint8_t OledShortRegData19[] = {0x11,0x08};
const uint8_t OledShortRegData20[] = {0x12,0x92};
const uint8_t OledShortRegData21[] = {0x13,0x00};
const uint8_t OledShortRegData22[] = {0x14,0x02};
const uint8_t OledShortRegData23[] = {0x15,0x05};
const uint8_t OledShortRegData24[] = {0x16,0x40};
const uint8_t OledShortRegData25[] = {0x17,0x03};
const uint8_t OledShortRegData26[] = {0x18,0x16};
const uint8_t OledShortRegData27[] = {0x19,0xd7};
const uint8_t OledShortRegData28[] = {0x1a,0x01};
const uint8_t OledShortRegData29[] = {0x1b,0xdc};  //01}; correction suite à l'erreur trouvé par la compagnie TDO
const uint8_t OledShortRegData30[] = {0x1c,0x00};
const uint8_t OledShortRegData31[] = {0x1d,0x04};
const uint8_t OledShortRegData32[] = {0x1e,0x00};
const uint8_t OledShortRegData33[] = {0x1f,0x00};
const uint8_t OledShortRegData34[] = {0x20,0x03};
const uint8_t OledShortRegData35[] = {0x21,0x16};
const uint8_t OledShortRegData36[] = {0x22,0x18};
const uint8_t OledShortRegData37[] = {0x23,0x08};
const uint8_t OledShortRegData38[] = {0x24,0xdc};
const uint8_t OledShortRegData39[] = {0x25,0x00};
const uint8_t OledShortRegData40[] = {0x26,0x04};
const uint8_t OledShortRegData41[] = {0x27,0x00};
const uint8_t OledShortRegData42[] = {0x28,0x00};
const uint8_t OledShortRegData43[] = {0x29,0x01};
const uint8_t OledShortRegData44[] = {0x2a,0x16};
const uint8_t OledShortRegData45[] = {0x2b,0x18};
const uint8_t OledShortRegData46[] = {0x2d,0x08};
const uint8_t OledShortRegData47[] = {0x4c,0x99};
const uint8_t OledShortRegData48[] = {0x4d,0x00};
const uint8_t OledShortRegData49[] = {0x4e,0x00};
const uint8_t OledShortRegData50[] = {0x4f,0x00};
const uint8_t OledShortRegData51[] = {0x50,0x01};
const uint8_t OledShortRegData52[] = {0x51,0x0A};
const uint8_t OledShortRegData53[] = {0x52,0x00};
const uint8_t OledShortRegData54[] = {0x5a,0xe4};
const uint8_t OledShortRegData55[] = {0x5e,0x77};
const uint8_t OledShortRegData56[] = {0x5f,0x77};
const uint8_t OledShortRegData57[] = {0x60,0x34};
const uint8_t OledShortRegData58[] = {0x61,0x02};
const uint8_t OledShortRegData59[] = {0x62,0x81};
const uint8_t OledShortRegData60[] = {0xFE,0x07};  //Page 6?
const uint8_t OledShortRegData61[] = {0x07,0x6D};
const uint8_t OledShortRegData62[] = {0xFE,0x01};
const uint8_t OledShortRegData63[] = {0x05,0x15};
const uint8_t OledShortRegData64[] = {0x0E,0x8B};
const uint8_t OledShortRegData65[] = {0x0F,0x8B};
const uint8_t OledShortRegData66[] = {0x10,0x11};
const uint8_t OledShortRegData67[] = {0x11,0xA2};
const uint8_t OledShortRegData68[] = {0x12,0xA0};
const uint8_t OledShortRegData69[] = {0x14,0xA1};
const uint8_t OledShortRegData70[] = {0x15,0x82};
const uint8_t OledShortRegData71[] = {0x18,0x47};
const uint8_t OledShortRegData72[] = {0x19,0x36};
const uint8_t OledShortRegData73[] = {0x1A,0x10};
const uint8_t OledShortRegData74[] = {0x1C,0x57};
const uint8_t OledShortRegData75[] = {0x1D,0x02};
const uint8_t OledShortRegData76[] = {0x21,0xF8};
const uint8_t OledShortRegData77[] = {0x22,0x90};
const uint8_t OledShortRegData78[] = {0x23,0x00};
const uint8_t OledShortRegData79[] = {0x25,0x03};
const uint8_t OledShortRegData80[] = {0x26,0x4a};
const uint8_t OledShortRegData81[] = {0x2A,0x83};
const uint8_t OledShortRegData82[] = {0X2B,0x4A};
const uint8_t OledShortRegData83[] = {0x2D,0x12};
const uint8_t OledShortRegData84[] = {0x2F,0x12};
const uint8_t OledShortRegData85[] = {0x30,0x45};
const uint8_t OledShortRegData86[] = {0x37,0x0C};
const uint8_t OledShortRegData87[] = {0x3a,0x00};
const uint8_t OledShortRegData88[] = {0x3b,0x20};
const uint8_t OledShortRegData89[] = {0x3d,0x0B};
const uint8_t OledShortRegData90[] = {0x3f,0x38};
const uint8_t OledShortRegData91[] = {0x40,0x0B};
const uint8_t OledShortRegData92[] = {0x41,0x0B};
const uint8_t OledShortRegData93[] = {0x42,0x33};
const uint8_t OledShortRegData94[] = {0x43,0x66};
const uint8_t OledShortRegData95[] = {0x44,0x11};
const uint8_t OledShortRegData96[] = {0x45,0x44};
const uint8_t OledShortRegData97[] = {0x46,0x22};
const uint8_t OledShortRegData98[] = {0x47,0x55};
const uint8_t OledShortRegData99[] = {0x4c,0x33};
const uint8_t OledShortRegData100[] = {0x4d,0x66};
const uint8_t OledShortRegData101[] = {0x4e,0x11};
const uint8_t OledShortRegData102[] = {0x4f,0x44};
const uint8_t OledShortRegData103[] = {0x50,0x22};
const uint8_t OledShortRegData104[] = {0x51,0x55};
const uint8_t OledShortRegData105[] = {0x56,0x11};
const uint8_t OledShortRegData106[] = {0x58,0x44};
const uint8_t OledShortRegData107[] = {0x59,0x22};
const uint8_t OledShortRegData108[] = {0x5a,0x55};
const uint8_t OledShortRegData109[] = {0x5b,0x33};
const uint8_t OledShortRegData110[] = {0x5c,0x66};
const uint8_t OledShortRegData111[] = {0x61,0x11};
const uint8_t OledShortRegData112[] = {0x62,0x44};
const uint8_t OledShortRegData113[] = {0x63,0x22};
const uint8_t OledShortRegData114[] = {0x64,0x55};
const uint8_t OledShortRegData115[] = {0x65,0x33};
const uint8_t OledShortRegData116[] = {0x66,0x66};
const uint8_t OledShortRegData117[] = {0x6d,0x90};
const uint8_t OledShortRegData118[] = {0x6e,0x40};
const uint8_t OledShortRegData119[] = {0x70,0xA5};
const uint8_t OledShortRegData120[] = {0x72,0x04};
const uint8_t OledShortRegData121[] = {0x73,0x15};
const uint8_t OledShortRegData122[] = {0x74,0x00};
const uint8_t OledShortRegData123[] = {0x75,0xF8};
const uint8_t OledShortRegData124[] = {0x76,0x90};
const uint8_t OledShortRegData125[] = {0xFE,0x0A};
const uint8_t OledShortRegData126[] = {0x29,0x10};
const uint8_t OledShortRegData127[] = {0xFE,0x05};
const uint8_t OledShortRegData128[] = {0x05,0x15}; //0x13};  //Selon la datasheet du IC, la valeur devrait être 20-21 (-2.5v, -2.4v) en décimale (0x14 ou 0x15) et non 0x13
const uint8_t OledShortRegData129[] = {0xFE,0x00};
const uint8_t OledShortRegData130[] = {0x35,0x00};
const uint8_t OledShortRegData131[] = {0x11,};  //Arguement 2 est vide
//Mettre un délai entre ces deux tableaux
const uint8_t OledShortRegData132[] = {0x29,};  //Arguement 2 est vide
const uint8_t OledShortRegData133[] = {0xC2, 0x03};  //Init DSI mode, FONCTIONNEL

const uint8_t OledShortRegData134[] = {0x51, 0xF0};  //Brightness command (0x00 = lower, 0xFF = Higher) ***Semble non fonctionnel
const uint8_t OledShortRegData135[] = {0x3a, 0x76};  //p.87, met l'écran en mode 24 bits. (bien que c'est le mode par défaut lors de l'init de l'écran)


/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup OTM8009A_Exported_Variables
  * @{
  */

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @defgroup OTM8009A_Exported_Functions OTM8009A Exported Functions
  * @{
  */

/**
  * @brief  DSI IO write short/long command.
  * @note : Can be surcharged by application code implementation of the function.
  */
__weak void DSI_IO_WriteCmd(uint32_t NbrParams, uint8_t *pParams)
{
  /* NOTE : This function Should not be modified, when it is needed,
            the DSI_IO_WriteCmd could be implemented in the user file
   */
}

/**
  * @brief  Initializes the LCD KoD display part by communication in DSI mode in Video Mode
  *         with IC Display Driver OTM8009A (see IC Driver specification for more information).
  * @param  hdsi_eval : pointer on DSI configuration structure
  * @param  hdsivideo_handle : pointer on DSI video mode configuration structure
  * @retval Status
  */
uint8_t OTM8009A_Init(uint32_t ColorCoding, uint32_t orientation)
{
  /* Enable CMD2 to access vendor specific commands                               */
  /* Enter in command 2 mode and set EXTC to enable address shift function (0x00) */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData1);
  DSI_IO_WriteCmd( 3, (uint8_t *)lcdRegData1);

  /* Enter ORISE Command 2 */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData2); /* Shift address to 0x80 */
  DSI_IO_WriteCmd( 2, (uint8_t *)lcdRegData2);

  /////////////////////////////////////////////////////////////////////
  /* SD_PCH_CTRL - 0xC480h - 129th parameter - Default 0x00          */
  /* Set SD_PT                                                       */
  /* -> Source output level during porch and non-display area to GND */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData2);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData3);
  OTM8009A_IO_Delay(10);
  /* Not documented */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData4);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData5);
  OTM8009A_IO_Delay(10);
  /////////////////////////////////////////////////////////////////////

  /* PWR_CTRL4 - 0xC4B0h - 178th parameter - Default 0xA8 */
  /* Set gvdd_en_test                                     */
  /* -> enable GVDD test mode !!!                         */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData6);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData7);

  /* PWR_CTRL2 - 0xC590h - 146th parameter - Default 0x79      */
  /* Set pump 4 vgh voltage                                    */
  /* -> from 15.0v down to 13.0v                               */
  /* Set pump 5 vgh voltage                                    */
  /* -> from -12.0v downto -9.0v                               */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData8);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData9);

  /* P_DRV_M - 0xC0B4h - 181th parameter - Default 0x00 */
  /* -> Column inversion                                */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData10);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData11);

  /* VCOMDC - 0xD900h - 1st parameter - Default 0x39h */
  /* VCOM Voltage settings                            */
  /* -> from -1.0000v downto -1.2625v                 */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData1);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData12);

  /* Oscillator adjustment for Idle/Normal mode (LPDT only) set to 65Hz (default is 60Hz) */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData13);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData14);

  /* Video mode internal */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData15);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData16);

  /* PWR_CTRL2 - 0xC590h - 147h parameter - Default 0x00 */
  /* Set pump 4&5 x6                                     */
  /* -> ONLY VALID when PUMP4_EN_ASDM_HV = "0"           */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData17);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData18);

  /* PWR_CTRL2 - 0xC590h - 150th parameter - Default 0x33h */
  /* Change pump4 clock ratio                              */
  /* -> from 1 line to 1/2 line                            */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData19);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData9);

  /* GVDD/NGVDD settings */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData1);
  DSI_IO_WriteCmd( 2, (uint8_t *)lcdRegData5);

  /* PWR_CTRL2 - 0xC590h - 149th parameter - Default 0x33h */
  /* Rewrite the default value !                           */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData20);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData21);

  /* Panel display timing Setting 3 */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData22);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData23);

  /* Power control 1 */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData24);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData25);

  /* Source driver precharge */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData13);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData26);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData15);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData27);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData28);
  DSI_IO_WriteCmd( 2, (uint8_t *)lcdRegData6);

  /* GOAVST */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData2);
  DSI_IO_WriteCmd( 6, (uint8_t *)lcdRegData7);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData29);
  DSI_IO_WriteCmd( 14, (uint8_t *)lcdRegData8);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData30);
  DSI_IO_WriteCmd( 14, (uint8_t *)lcdRegData9);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData31);
  DSI_IO_WriteCmd( 10, (uint8_t *)lcdRegData10);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData32);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData46);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData2);
  DSI_IO_WriteCmd( 10, (uint8_t *)lcdRegData11);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData33);
  DSI_IO_WriteCmd( 15, (uint8_t *)lcdRegData12);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData29);
  DSI_IO_WriteCmd( 15, (uint8_t *)lcdRegData13);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData30);
  DSI_IO_WriteCmd( 10, (uint8_t *)lcdRegData14);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData31);
  DSI_IO_WriteCmd( 15, (uint8_t *)lcdRegData15);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData32);
  DSI_IO_WriteCmd( 15, (uint8_t *)lcdRegData16);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData34);
  DSI_IO_WriteCmd( 10, (uint8_t *)lcdRegData17);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData35);
  DSI_IO_WriteCmd( 10, (uint8_t *)lcdRegData18);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData2);
  DSI_IO_WriteCmd( 10, (uint8_t *)lcdRegData19);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData33);
  DSI_IO_WriteCmd( 15, (uint8_t *)lcdRegData20);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData29);
  DSI_IO_WriteCmd( 15, (uint8_t *)lcdRegData21);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData30);
  DSI_IO_WriteCmd( 10, (uint8_t *)lcdRegData22);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData31);
  DSI_IO_WriteCmd( 15, (uint8_t *)lcdRegData23);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData32);
  DSI_IO_WriteCmd( 15, (uint8_t *)lcdRegData24);

  /////////////////////////////////////////////////////////////////////////////
  /* PWR_CTRL1 - 0xc580h - 130th parameter - default 0x00 */
  /* Pump 1 min and max DM                                */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData13);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData47);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData48);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData49);
  /////////////////////////////////////////////////////////////////////////////

  /* CABC LEDPWM frequency adjusted to 19,5kHz */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData50);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData51);
  
  /* Exit CMD2 mode */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData1);
  DSI_IO_WriteCmd( 3, (uint8_t *)lcdRegData25);

  /*************************************************************************** */
  /* Standard DCS Initialization TO KEEP CAN BE DONE IN HSDT                   */
  /*************************************************************************** */

  /* NOP - goes back to DCS std command ? */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData1);
          
  /* Gamma correction 2.2+ table (HSDT possible) */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData1);
  DSI_IO_WriteCmd( 16, (uint8_t *)lcdRegData3);
  
  /* Gamma correction 2.2- table (HSDT possible) */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData1);
  DSI_IO_WriteCmd( 16, (uint8_t *)lcdRegData4);
          
  /* Send Sleep Out command to display : no parameter */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData36);
  
  /* Wait for sleep out exit */
  OTM8009A_IO_Delay(120);

  switch(ColorCoding)
  {
  case OTM8009A_FORMAT_RBG565 :
    /* Set Pixel color format to RGB565 */
    DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData37);
    break;
  case OTM8009A_FORMAT_RGB888 :
    /* Set Pixel color format to RGB888 */
    DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData38);
    break;
  default :
    break;
  }

  /* Send command to configure display in landscape orientation mode. By default
      the orientation mode is portrait  */
  if(orientation == OTM8009A_ORIENTATION_LANDSCAPE)
  {
    DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData39);
    DSI_IO_WriteCmd( 4, (uint8_t *)lcdRegData27);
    DSI_IO_WriteCmd( 4, (uint8_t *)lcdRegData28);
  }

  /** CABC : Content Adaptive Backlight Control section start >> */
  /* Note : defaut is 0 (lowest Brightness), 0xFF is highest Brightness, try 0x7F : intermediate value */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData40);

  /* defaut is 0, try 0x2C - Brightness Control Block, Display Dimming & BackLight on */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData41);

  /* defaut is 0, try 0x02 - image Content based Adaptive Brightness [Still Picture] */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData42);

  /* defaut is 0 (lowest Brightness), 0xFF is highest Brightness */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData43);

  /** CABC : Content Adaptive Backlight Control section end << */

  /* Send Command Display On */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData44);

  /* NOP command */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData1);

  /* Send Command GRAM memory write (no parameters) : this initiates frame write via other DSI commands sent by */
  /* DSI host from LTDC incoming pixels in video mode */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData45);

  return 0;
}

/**
  * @brief  Initializes the LCD KoD display part by communication in DSI mode in Video Mode
  *         with IC Display Driver OTM8009A (see IC Driver specification for more information).
  * @param  hdsi_eval : pointer on DSI configuration structure
  * @param  hdsivideo_handle : pointer on DSI video mode configuration structure
  * @retval Status
  */
uint8_t OTM8009A_Init_OLED()
{
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData1);  //Commandes d'écran OLED selon le PDF
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData2);  //RM67160_initial_code_for_custom_V8...
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData3);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData4);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData5);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData6);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData7);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData8);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData9);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData10);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData11);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData12);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData13);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData14);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData15);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData16);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData17);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData18);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData19);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData20);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData21);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData22);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData23);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData24);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData25);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData26);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData27);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData28);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData29);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData30);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData31);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData32);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData33);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData34);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData35);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData36);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData37);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData38);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData39);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData40);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData41);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData42);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData43);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData44);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData45);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData46);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData47);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData48);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData49);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData50);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData51);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData52);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData53);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData54);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData55);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData56);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData57);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData58);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData59);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData60);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData61);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData62);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData63);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData64);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData65);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData66);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData67);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData68);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData69);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData70);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData71);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData72);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData73);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData74);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData75);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData76);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData77);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData78);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData79);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData80);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData81);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData82);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData83);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData84);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData85);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData86);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData87);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData88);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData89);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData90);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData91);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData92);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData93);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData94);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData95);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData96);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData97);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData98);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData99);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData100);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData101);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData102);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData103);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData104);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData105);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData106);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData107);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData108);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData109);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData110);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData111);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData112);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData113);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData114);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData115);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData116);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData117);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData118);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData119);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData120);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData121);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData122);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData123);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData124);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData125);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData126);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData127);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData128);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData129);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData130);
	DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData131);

	//Les commandes commentées ci-dessous ne change rien (sauf Brightness pour plus tard)
	//DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData133);  //Init en mode DSI, avec commande qui demande à ajuster le timming en mode auto (driver)
	//DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData135);  //Mode 24 bits
	//DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData134);  //Brightness

  /* Wait for sleep out exit */
  OTM8009A_IO_Delay(120);

  DSI_IO_WriteCmd(0, (uint8_t *)OledShortRegData132);  //Commande de démarrage?

  return 0;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
