/*
 * canbus.c
 *
 *  Created on: 14 mai 2018
 *      Author: TophersMSI
 */

/*------------------- includes -------------------*/
#include <string.h>
#include <stdbool.h>
#include "canbus.h"

/*------------------- Prototypes -------------------*/


/*------------------- Variables globales -------------------*/
CAN_HandleTypeDef CanHandle;

CAN_FilterTypeDef  sFilterConfig;
CAN_TxHeaderTypeDef   TxHeader;
CAN_RxHeaderTypeDef   RxHeader;
uint8_t               TxData[8];
uint8_t               RxData[8];
uint32_t              TxMailbox;

extern uint8_t val_SliderR;
extern uint8_t val_SliderG;
extern uint8_t val_SliderB;
extern bool can_mode_master;

/*------------------- Entré du programme -------------------*/
void canbusInit()
{
	/*##-1- Configure the CAN peripheral #######################################*/
	  CanHandle.Instance = CAN1;

	  CanHandle.Init.TimeTriggeredMode = DISABLE;
	  CanHandle.Init.AutoBusOff = DISABLE;
	  CanHandle.Init.AutoWakeUp = DISABLE;
	  CanHandle.Init.AutoRetransmission = DISABLE;  //ENABLE;
	  CanHandle.Init.ReceiveFifoLocked = DISABLE;
	  CanHandle.Init.TransmitFifoPriority = DISABLE;
	  CanHandle.Init.Mode = CAN_MODE_NORMAL; //CAN_MODE_LOOPBACK;
	  CanHandle.Init.SyncJumpWidth = CAN_SJW_1TQ;
	  CanHandle.Init.TimeSeg1 = CAN_BS1_6TQ;
	  CanHandle.Init.TimeSeg2 = CAN_BS2_2TQ;
	  CanHandle.Init.Prescaler = 6;

	  if(HAL_CAN_Init(&CanHandle) != HAL_OK)
	  {
	    /* Initialization Error */
	    Error_Handler();
	  }

	  /*##-2- Configure the CAN Filter ###########################################*/
	  sFilterConfig.FilterBank = 0;
	  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	  sFilterConfig.FilterIdHigh = 0x0000;
	  sFilterConfig.FilterIdLow = 0x0000;
	  sFilterConfig.FilterMaskIdHigh = 0x0000;
	  sFilterConfig.FilterMaskIdLow = 0x0000;
	  sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	  sFilterConfig.FilterActivation = ENABLE;
	  sFilterConfig.SlaveStartFilterBank = 14;

	  if(HAL_CAN_ConfigFilter(&CanHandle, &sFilterConfig) != HAL_OK)
	  {
	    /* Filter configuration Error */
	    Error_Handler();
	  }

	  /*##-3- Start the CAN peripheral ###########################################*/
	  if (HAL_CAN_Start(&CanHandle) != HAL_OK)
	  {
	    /* Start Error */
	    Error_Handler();
	  }

	  HAL_CAN_ActivateNotification(&CanHandle, CAN_IT_RX_FIFO0_MSG_PENDING);
	  HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 5, 0);
	  HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
}

/**
  * @brief  Configures the CAN, transmit and receive by polling
  * @param  None
  * @retval PASSED if the reception is well done, FAILED in other case
  */
HAL_StatusTypeDef CAN_Polling(void)
{
	/*##-4- Start the Transmission process #####################################*/
	  TxHeader.StdId = 0x11;
	  TxHeader.RTR = CAN_RTR_DATA;
	  TxHeader.IDE = CAN_ID_STD;
	  TxHeader.DLC = 2;
	  TxHeader.TransmitGlobalTime = DISABLE;
	  TxData[0] = 0xCA;
	  TxData[1] = 0xFE;

	  /* Request transmission */
	  if(HAL_CAN_AddTxMessage(&CanHandle, &TxHeader, TxData, &TxMailbox) != HAL_OK)
	  {
	    /* Transmission request Error */
	    Error_Handler();
	  }

	  /* Wait transmission complete */
	  while(HAL_CAN_GetTxMailboxesFreeLevel(&CanHandle) != 3) {}

	  /*##-5- Start the Reception process ########################################*/
	  if(HAL_CAN_GetRxFifoFillLevel(&CanHandle, CAN_RX_FIFO0) != 1)
	  {
	    /* Reception Missing */
	    Error_Handler();
	  }

	  if(HAL_CAN_GetRxMessage(&CanHandle, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
	  {
	    /* Reception Error */
	    Error_Handler();
	  }

	  if((RxHeader.StdId != 0x11)                     ||
	     (RxHeader.RTR != CAN_RTR_DATA)               ||
	     (RxHeader.IDE != CAN_ID_STD)                 ||
	     (RxHeader.DLC != 2)                          ||
	     ((RxData[0]<<8 | RxData[1]) != 0xCAFE))
	  {
	    /* Rx message Error */
	    return HAL_ERROR;
	  }

	  return HAL_OK; /* Test Passed */
}

void canbusReceive()
{

}

HAL_StatusTypeDef canbusWrite(uint8_t *data, uint8_t dataLenght)
{
	TxHeader.StdId = 0x11;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.DLC = dataLenght;
	TxHeader.TransmitGlobalTime = DISABLE;

	//Construction de la trame
	for(int i=0; i<dataLenght; i++)
	{
		TxData[i] = data[i];
	}

	/* Request transmission */
	if(HAL_CAN_AddTxMessage(&CanHandle, &TxHeader, TxData, &TxMailbox) != HAL_OK)
	{
		/* Transmission request Error */
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

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	/*##-5- Start the Reception process ########################################*/
	  if(HAL_CAN_GetRxFifoFillLevel(hcan, CAN_RX_FIFO0) != 1)
	  {
	    /* Reception Missing */
	    Error_Handler();
	  }

	  if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
	  {
	    /* Reception Error */
	    Error_Handler();
	  }

	  /*
	  if((RxHeader.StdId != 0x11)                     ||
	     (RxHeader.RTR != CAN_RTR_DATA)               ||
	     (RxHeader.IDE != CAN_ID_STD)                 ||
	     (RxHeader.DLC != 2)                          ||
	     ((RxData[0]<<8 | RxData[1]) != 0xCAFE))
	  {
	    Error_Handler();
	  }
	   */

	  if(can_mode_master == false){
		  if(RxHeader.DLC == 3){  //Valeur de trois bytes (RGB)
			  val_SliderR = TxData[0];  //Modifie les valeurs présentes dans le main
			  val_SliderG = TxData[1];
			  val_SliderB = TxData[2];
		  }
	  }
}
