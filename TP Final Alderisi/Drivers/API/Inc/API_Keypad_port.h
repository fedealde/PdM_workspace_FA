/*
 * API_Keypad_port.h
 *
 *  Created on: Apr 15, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_KEYPAD_PORT_H_
#define API_INC_API_KEYPAD_PORT_H_

//Includes
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

//Number of columns
#define NUM_OF_COLS 4
#define NUM_OF_ROWS 4

//Definition for ON and OFF
#define ON true
#define OFF false

/**
 * @brief Initialize GPIO port
 *
 */
void KeypadPortGPIOInit(void);
/**
 * @brief Read keypad GPIO port and return state
 *
 * @param Port
 * @param Pin
 * @return State of GPIO (true is ON and false is OFF)
 */
bool KeypadPortPinRead(GPIO_TypeDef *Port, uint16_t Pin);
/**
 * @brief Write keypad GPIO port
 *
 * @param Port
 * @param Pin
 * @param State
 */
void KeypadPortPinWrite(GPIO_TypeDef *Port, uint16_t Pin, GPIO_PinState State);

#endif /* API_INC_API_KEYPAD_PORT_H_ */
