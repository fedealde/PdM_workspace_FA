/*
 * API_LCD_port.h
 *
 *  Created on: Apr 4, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_LCD_PORT_H_
#define API_INC_API_LCD_PORT_H_

#include "API_I2C.h"

#define LCD_ADD 0x27 //Address defined by user
#define LCD_SEND_DELAY_10MS 10 //Delay tosend

#define LCD_ADD_SHIFTED (LCD_ADD<<1) // Address shifted before to send

/**
 * @brief Initialize the LCD port communication
 *
 * @return True if successful and false if error
 */
bool LCDPortInit(void);
/**
 * @brief Function to send port byte data
 *
 * @param data
 * @return True if successful and false if error
 */
bool LCDPortSendByte(uint8_t data);
/**
 * @brief Delay, from port to use in LCD
 *
 * @param delay
 */
void LCDPortDelay(uint32_t delay);
/**
 * @brief Error function handler for port
 *
 */
void LCDPortErrorHandler(void);

#endif /* API_INC_API_LCD_PORT_H_ */
