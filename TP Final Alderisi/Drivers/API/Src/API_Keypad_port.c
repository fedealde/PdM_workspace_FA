/*
 * API_Keypad_port.c
 *
 *  Created on: Apr 15, 2024
 *      Author: flealu
 */

#include "API_Keypad_port.h"

const uint16_t COLS_PINS_ARRAY[] = { C1, C2, C3, C4 };
GPIO_TypeDef *COLS_PORTS_ARRAY[] = { C1_Port, C2_Port, C3_Port, C4_Port };

const uint16_t ROWS_PINS_ARRAY[] = { R1, R2, R3, R4 };
GPIO_TypeDef *ROWS_PORTS_ARRAY[] = { R1_Port, R2_Port, R3_Port, R4_Port };

void KeypadPortGPIOInit(void) {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	HAL_GPIO_WritePin(R1_Port, R1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(R3_Port, R3 | R4 | C1 | C2 | C3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(R2_Port, R2 | C4, GPIO_PIN_RESET);

	for (uint8_t i = 0; i < NUM_OF_COLS; i++) {

		GPIO_InitStruct.Pin = COLS_PINS_ARRAY[i];
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(COLS_PORTS_ARRAY[i], &GPIO_InitStruct);

	}

	for (uint8_t i = 0; i < NUM_OF_ROWS; i++) {

		GPIO_InitStruct.Pin = ROWS_PINS_ARRAY[i];
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(ROWS_PORTS_ARRAY[i], &GPIO_InitStruct);

	}

}

bool KeypadPortPinRead(GPIO_TypeDef *Port, uint16_t Pin) {

	if (HAL_GPIO_ReadPin(Port, Pin) == GPIO_PIN_SET) {
		return true;
	}

	return false;

}

void KeypadPortPinWrite(GPIO_TypeDef *Port, uint16_t Pin, GPIO_PinState State) {

	HAL_GPIO_WritePin(Port, Pin, State);

}

