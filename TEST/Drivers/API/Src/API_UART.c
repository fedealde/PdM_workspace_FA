/*
 * API_UART.c
 *
 *  Created on: Mar 30, 2024
 *      Author: flealu
 */

#include <API_UART.h>

#define CHARACTER_SIZE 1
#define TIMEOUT_UART 10
#define BASE 10
#define BUFFER_SIZE 50

static UART_HandleTypeDef UARTHandle;
static void UARTErrorHandler(void);

bool UARTInit(void) {

	char BUFFER[BUFFER_SIZE];

	UARTHandle.Instance = USARTx;

	UARTHandle.Init.BaudRate = 9600;
	UARTHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UARTHandle.Init.StopBits = UART_STOPBITS_1;
	UARTHandle.Init.Parity = UART_PARITY_ODD;
	UARTHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UARTHandle.Init.Mode = UART_MODE_TX_RX;
	UARTHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&UARTHandle) != HAL_OK) {

		UARTErrorHandler();

		return false;

	}

	//print UART information
	UARTSendString((uint8_t*) "\n__________________\n\0");
	UARTSendString((uint8_t*) "\nUART CONFIGURATION: \0");
	UARTSendString((uint8_t*) "\n#BaudRate: \0");
	UARTSendString((uint8_t*) itoa(UARTHandle.Init.BaudRate, BUFFER, BASE));
	UARTSendString((uint8_t*) "\n#WordLength: \0");
	UARTSendString((uint8_t*) itoa(UARTHandle.Init.WordLength, BUFFER, BASE));
	UARTSendString((uint8_t*) "\n#StopBits: \0");
	UARTSendString((uint8_t*) itoa(UARTHandle.Init.StopBits, BUFFER, BASE));
	UARTSendString((uint8_t*) "\n#Parity: \0");
	UARTSendString((uint8_t*) itoa(UARTHandle.Init.Parity, BUFFER, BASE));
	UARTSendString((uint8_t*) "\n#HwFlowCtl: \0");
	UARTSendString((uint8_t*) itoa(UARTHandle.Init.HwFlowCtl, BUFFER, BASE));
	UARTSendString((uint8_t*) "\n#Mode: \0");
	UARTSendString((uint8_t*) itoa(UARTHandle.Init.Mode, BUFFER, BASE));
	UARTSendString((uint8_t*) "\n#OverSampling: \0");
	UARTSendString((uint8_t*) itoa(UARTHandle.Init.OverSampling, BUFFER, BASE));
	UARTSendString((uint8_t*) "\n__________________\n");

	return true;

}

void UARTSendString(uint8_t *pstring) {

	if (pstring != NULL) {
		while (*pstring != '\0') {
			HAL_UART_Transmit(&UARTHandle, pstring, CHARACTER_SIZE,
			TIMEOUT_UART);
			pstring++;
		}
	} else {

		UARTErrorHandler();

	}

}

void UARTSendStringSize(uint8_t *pstring, uint16_t size) {

	if (pstring != NULL) {

		if (HAL_UART_Transmit(&UARTHandle, pstring, size, TIMEOUT_UART)
				!= HAL_OK) {

			UARTErrorHandler();

		}

	} else {

		UARTErrorHandler();
	}

}

void UARTReceiveStringSize(uint8_t *pstring, uint16_t size) {

	HAL_UART_Receive(&UARTHandle, pstring, size, TIMEOUT_UART);

}

//static error handler
static void UARTErrorHandler(void) {

	while (1)
		;

}

