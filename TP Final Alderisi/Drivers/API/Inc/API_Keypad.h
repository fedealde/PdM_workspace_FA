/*
 * API_Keypad.h
 *
 *  Created on: Apr 15, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_KEYPAD_H_
#define API_INC_API_KEYPAD_H_

//includes
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Initialize the Keypad
 *
 */
void KeypadInit(void);
/**
 * @brief Initialize keypad debounce FSM
 *
 */
void KeypadDebounceFSMInit(void);
/**
 * @brief Function to update keypad debounce FSM
 *
 * @return
 */
char KeypadDebounceFSMUpdate(void);

#endif /* API_INC_API_KEYPAD_H_ */
