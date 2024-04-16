/*
 * API_debounce.h
 *
 *  Created on: Mar 24, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include "API_Delay.h"
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"


void debounceFSM_init(void);	// debe cargar el estado inicial
void debounceFSM_update(void);	// debe leer las entradas, resolver la lógica de
// transición de estados y actualizar las salidas
bool_t readKey(void); //It returns the state y the button was pressed
bool_t readRisingEdge (void);//Read and return state edge, then reset
bool_t readFallingEdge (void);//Read and return state edge, then reset

#endif /* API_INC_API_DEBOUNCE_H_ */
