/*
 * API_Keypad.h
 *
 *  Created on: Apr 15, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_KEYPAD_H_
#define API_INC_API_KEYPAD_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

void KeypadInit(void);

char KeypadScan(void);

void KeypadDebounceFSMInit(void);

char KeypadDebounceFSMUpdate(void);

#endif /* API_INC_API_KEYPAD_H_ */
