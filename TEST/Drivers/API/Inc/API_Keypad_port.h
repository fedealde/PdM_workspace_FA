/*
 * API_Keypad_port.h
 *
 *  Created on: Apr 15, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_KEYPAD_PORT_H_
#define API_INC_API_KEYPAD_PORT_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>


//COLUMNS DEFINITIONS (READ PINS)
#define C1 GPIO_PIN_12
#define C1_Port GPIOB
#define C2 GPIO_PIN_13
#define C2_Port GPIOB
#define C3 GPIO_PIN_15
#define C3_Port GPIOB
#define C4 GPIO_PIN_6
#define C4_Port GPIOC

//ROWS DEFINITIONS (WRITE PINS)
#define R1 GPIO_PIN_15
#define R1_Port GPIOA
#define R2 GPIO_PIN_7
#define R2_Port GPIOC
#define R3 GPIO_PIN_5
#define R3_Port GPIOB
#define R4 GPIO_PIN_3
#define R4_Port GPIOB

#define NUM_OF_COLS 4
#define NUM_OF_ROWS 4

#define ON true
#define OFF false

void KeypadPortGPIOInit(void);
bool KeypadPortPinRead(GPIO_TypeDef * Port, uint16_t Pin);
void KeypadPortPinWrite(GPIO_TypeDef * Port, uint16_t Pin, GPIO_PinState State);

#endif /* API_INC_API_KEYPAD_PORT_H_ */
