/*
 * API_uart.h
 *
 *  Created on: Mar 30, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

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
