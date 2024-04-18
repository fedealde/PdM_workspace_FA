/*
 * API_debounce.h
 *
 *  Created on: Mar 24, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

typedef bool bool_t;

/**
 * @brief Initialize debounce FSM
 *
 */
void debounceFSM_init(void);
/**
 * @brief Update debounce FSM
 *
 */
void debounceFSM_update(void);
//
/**
 * @brief Read a button state
 *
 * @return It returns the state when the button was pressed
 */
bool_t readKey(void);
/**
 * @brief Read raising state edge, then reset state
 *
 * @return Return raising state edge
 */
bool_t readRisingEdge(void);
/**
 * @brief Read falling state edge, then reset state
 *
 * @return Return falling state edge
 */
bool_t readFallingEdge(void);

#endif /* API_INC_API_DEBOUNCE_H_ */
