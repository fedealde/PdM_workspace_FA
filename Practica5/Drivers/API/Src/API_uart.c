/*
 * API_uart.c
 *
 *  Created on: Mar 30, 2024
 *      Author: flealu
 */

#include <stdlib.h>
#include "main.h"
#include "API_uart.h"
#include "stm32f4xx_hal_uart.h"

#define CHARACTER_SIZE 1
#define TIMEOUT_UART 10
#define BUFFER_SIZE 20

static UART_HandleTypeDef UartHandle;
static void Error_Handler(void);

bool uartInit(void){

	char BUFFER [BUFFER_SIZE];

	UartHandle.Instance = USARTx;

	UartHandle.Init.BaudRate = 9600;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits = UART_STOPBITS_1;
	UartHandle.Init.Parity = UART_PARITY_ODD;
	UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&UartHandle) != HAL_OK){

		Error_Handler();

		return false;

	}

	uartSendString((uint8_t *) "__________________\n\0");
	uartSendString((uint8_t *) "\nUART CONFIGURATION: \0");
	uartSendString((uint8_t *) "\n#BaudRate: \0");
	uartSendString((uint8_t*) itoa(UartHandle.Init.BaudRate, BUFFER, TIMEOUT_UART));
	uartSendString((uint8_t *) "\n#WordLength: \0");
	uartSendString((uint8_t*) itoa(UartHandle.Init.WordLength, BUFFER, TIMEOUT_UART));
	uartSendString((uint8_t *) "\n#StopBits: \0");
	uartSendString((uint8_t*) itoa(UartHandle.Init.StopBits, BUFFER, TIMEOUT_UART));
	uartSendString((uint8_t *) "\n#Parity: \0");
	uartSendString((uint8_t*) itoa(UartHandle.Init.Parity, BUFFER, TIMEOUT_UART));
	uartSendString((uint8_t *) "\n#HwFlowCtl: \0");
	uartSendString((uint8_t*) itoa(UartHandle.Init.HwFlowCtl, BUFFER, TIMEOUT_UART));
	uartSendString((uint8_t *) "\n#Mode: \0");
	uartSendString((uint8_t*) itoa(UartHandle.Init.Mode, BUFFER, TIMEOUT_UART));
	uartSendString((uint8_t *) "\n#OverSampling: \0");
	uartSendString((uint8_t*) itoa(UartHandle.Init.OverSampling, BUFFER, TIMEOUT_UART));
	uartSendString((uint8_t *) "\n__________________\n");

	return true;


}



void uartSendString(uint8_t * pstring){

	if(pstring != NULL)
	{
	while(*pstring != '\0')
	{
		HAL_UART_Transmit(&UartHandle, pstring, CHARACTER_SIZE, TIMEOUT_UART);
		pstring++;
	}
	}else{

		Error_Handler();

	}

}




void uartSendStringSize(uint8_t * pstring, uint16_t size){


	if(pstring != NULL)
	{

		if(HAL_UART_Transmit(&UartHandle, pstring, size, TIMEOUT_UART) != HAL_OK){

		Error_Handler();

		}

	}else {

		Error_Handler();
	}


}






void uartReceiveStringSize(uint8_t * pstring, uint16_t size){


	if(HAL_UART_Receive(&UartHandle, pstring, size, TIMEOUT_UART) != HAL_OK){

		Error_Handler();

	}


}


static void Error_Handler(void){

	BSP_LED_On(LED_RED);
	while(1);

}




