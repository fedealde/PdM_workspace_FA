/*
 * API_UART.h
 *
 *  Created on: Mar 30, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

//Includes
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"


/* Definition for USARTx clock resources and GPIOs*/
#define USARTx                           USART3
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_8
#define USARTx_TX_GPIO_PORT              GPIOD
#define USARTx_TX_AF                     GPIO_AF7_USART3
#define USARTx_RX_PIN                    GPIO_PIN_9
#define USARTx_RX_GPIO_PORT              GPIOD
#define USARTx_RX_AF                     GPIO_AF7_USART3

/**
 * @brief initialize UART for stlink, print configuration through UART.
 *
 * @return true or false depending on success
 */
bool UARTInit(void);

/**
 * @brief send pstring through UART, character by character until \0 or NULL is found
 *
 * @param pstring
 */
void UARTSendString(uint8_t *pstring);

/**
 * @brief send pstring thorough UART, using the size as limit of sent information
 *
 * @param pstring
 * @param size
 */
void UARTSendStringSize(uint8_t *pstring, uint16_t size);

/**
 * @brief receive information from UART, specifying maximun size
 *
 * @param pstring
 * @param size
 */
void UARTReceiveStringSize(uint8_t *pstring, uint16_t size);

#endif /* API_INC_API_UART_H_ */
