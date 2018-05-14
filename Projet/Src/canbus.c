/*
 * canbus.c
 *
 *  Created on: 14 mai 2018
 *      Author: TophersMSI
 */

/*------------------- includes -------------------*/
#include "canbus.h"

/*------------------- Variables globales -------------------*/
CAN_HandleTypeDef CanHandle;

CAN_FilterConfTypeDef  sFilterConfig;
static CanTxMsgTypeDef        TxMessage;
static CanRxMsgTypeDef        RxMessage;

/*------------------- Entré du programme -------------------*/
void canbusInit()
{
  //CAN_FilterConfTypeDef  sFilterConfig;
  //static CanTxMsgTypeDef        TxMessage;
  //static CanRxMsgTypeDef        RxMessage;

  /*##-1- Configure the CAN peripheral #######################################*/
  CanHandle.Instance = CAN1;
  CanHandle.pTxMsg = &TxMessage;
  CanHandle.pRxMsg = &RxMessage;

  CanHandle.Init.TTCM = DISABLE;
  CanHandle.Init.ABOM = DISABLE;
  CanHandle.Init.AWUM = DISABLE;
  CanHandle.Init.NART = DISABLE;
  CanHandle.Init.RFLM = DISABLE;
  CanHandle.Init.TXFP = DISABLE;
  CanHandle.Init.Mode = CAN_MODE_LOOPBACK; 	//CAN_MODE_NORMAL;  //CanHandle.Init.Mode = CAN_MODE_LOOPBACK;
  CanHandle.Init.SJW  = CAN_SJW_1TQ;
  CanHandle.Init.BS1  = CAN_BS1_6TQ;
  CanHandle.Init.BS2  = CAN_BS2_7TQ;
  CanHandle.Init.Prescaler = 4;

  if(HAL_CAN_Init(&CanHandle) != HAL_OK)
  {
	/* Initialization Error */
	Error_Handler();
  }

  /*##-2- Configure the CAN Filter ###########################################*/
  sFilterConfig.FilterNumber = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = 0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.BankNumber = 14;

  if(HAL_CAN_ConfigFilter(&CanHandle, &sFilterConfig) != HAL_OK)
  {
	/* Filter configuration Error */
	Error_Handler();
  }

  //Ajout personnel pour activer les interrupts
  //__HAL_CAN_ENABLE_IT(CanHandle, );
  HAL_CAN_Receive_IT(&CanHandle, 1);
}

/**
  * @brief  Configures the CAN, transmit and receive by polling
  * @param  None
  * @retval PASSED if the reception is well done, FAILED in other case
  */
HAL_StatusTypeDef CAN_Polling(void)
{
  /*##-3- Start the Transmission process #####################################*/
  CanHandle.pTxMsg->StdId = 0x11;
  CanHandle.pTxMsg->RTR = CAN_RTR_DATA;
  CanHandle.pTxMsg->IDE = CAN_ID_STD;
  CanHandle.pTxMsg->DLC = 2;
  CanHandle.pTxMsg->Data[0] = 0xCA;
  CanHandle.pTxMsg->Data[1] = 0xFE;

  if(HAL_CAN_Transmit(&CanHandle, 10) != HAL_OK)
  {
    /* Transmition Error */
    Error_Handler();
  }

  if(HAL_CAN_GetState(&CanHandle) != HAL_CAN_STATE_READY)
  {
    return HAL_ERROR;
  }

  /*##-4- Start the Reception process ########################################*/
  if(HAL_CAN_Receive(&CanHandle, CAN_FIFO0,10) != HAL_OK)
  {
    /* Reception Error */
    Error_Handler();
  }

  if(HAL_CAN_GetState(&CanHandle) != HAL_CAN_STATE_READY)
  {
    return HAL_ERROR;
  }

  if(CanHandle.pRxMsg->StdId != 0x11)
  {
    return HAL_ERROR;
  }

  if(CanHandle.pRxMsg->IDE != CAN_ID_STD)
  {
    return HAL_ERROR;
  }

  if(CanHandle.pRxMsg->DLC != 2)
  {
    return HAL_ERROR;
  }

  if((CanHandle.pRxMsg->Data[0]<<8|RxMessage.Data[1]) != 0xCAFE)
  {
    return HAL_ERROR;
  }

  return HAL_OK; /* Test Passed */
}

void canbusReceive()
{

}

HAL_StatusTypeDef canbusWrite(uint8_t *data, uint8_t dataLenght)
{
	/*##-3- Start the Transmission process #####################################*/
  CanHandle.pTxMsg->StdId = 0x11;
  CanHandle.pTxMsg->RTR = CAN_RTR_DATA;
  CanHandle.pTxMsg->IDE = CAN_ID_STD;
  CanHandle.pTxMsg->DLC = 2;
  if(dataLenght >= 64)
	  return HAL_ERROR;

  for(int i=0; i<dataLenght; i++)  //Fonction qui remplie le buffer (max 8 bytes) de données à envoyer
  {
	  CanHandle.pTxMsg->Data[i] = data[i];
  }
  //CanHandle.pTxMsg->Data[0] = 0xCA;
  //CanHandle.pTxMsg->Data[1] = 0xFE;

  if(HAL_CAN_Transmit(&CanHandle, 10) != HAL_OK)
  {
	/* Transmition Error */
	Error_Handler();
  }

  if(HAL_CAN_GetState(&CanHandle) != HAL_CAN_STATE_READY)
  {
	return HAL_ERROR;
  }

  return HAL_OK; /* Test Passed */
}

void canbusPollingTest()
{
	if(CAN_Polling() == HAL_OK)
	{
	  /* OK: Turn on LED6 */
	  BSP_LED_On(LED_GREEN);
	}
	else
	{
	  /* KO: Turn on LED5 */
	  BSP_LED_On(LED_RED);
	}
}

void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan)
{
	int i =0;
	i++;
}
