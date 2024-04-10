/*
 * API_LCD_port.h
 *
 *  Created on: Apr 4, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_LCD_PORT_H_
#define API_INC_API_LCD_PORT_H_

#include "API_I2C.h"

#define LCD_ADD 0x27 //DEFINIR ANTES DE UTILIZAR!!!!!!!!!!!!!!!!!!!!!!!!!!
#define LCD_SEND_DELAY_10MS 10

#define LCD_ADD_SHIFTED (LCD_ADD<<1)

bool LCDPortInit (void);
bool LCDPortSendByte(uint8_t data);
void LCDPortDelay (uint32_t delay);
void LCDPortErrorHandler(void);


#endif /* API_INC_API_LCD_PORT_H_ */
