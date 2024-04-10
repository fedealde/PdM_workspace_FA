/*
 * API_uart.h
 *
 *  Created on: Mar 30, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_


/* User can use this section to tailor USARTx/UARTx instance used and associated
   resources */
/* Definition for USARTx clock resources */
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
 * @brief initialize uart for stlink, print configuration through uart.
 *
 * @return true or false depending on success
 */
bool uartInit(void);

/**
 * @brief send pstring through uart, character by character until \0 or NULL is found
 *
 * @param pstring
 */
void uartSendString(uint8_t * pstring);

/**
 * @brief send pstring thorough uart, using the size as limit of sent information
 *
 * @param pstring
 * @param size
 */
void uartSendStringSize(uint8_t * pstring, uint16_t size);

/**
 * @brief receive information from uart, specifying maximun size
 *
 * @param pstring
 * @param size
 */
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);


#endif /* API_INC_API_UART_H_ */
