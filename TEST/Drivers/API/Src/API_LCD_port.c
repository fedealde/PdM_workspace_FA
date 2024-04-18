/*
 * API_LCD_port.c
 *
 *  Created on: Apr 4, 2024
 *      Author: flealu
 */

#include "API_LCD_port.h"

extern I2C_HandleTypeDef hi2c1;

bool LCDPortInit(void) {
	return I2C1Init();
}

bool LCDPortSendByte(uint8_t data) {

	if (HAL_I2C_Master_Transmit(&hi2c1, LCD_ADD_SHIFTED, &data, sizeof(data),
	LCD_SEND_DELAY_10MS) != HAL_OK) {
		return false;
	}

	return true;

}

void LCDPortDelay(uint32_t delay) {

	HAL_Delay(delay);

}

void LCDPortErrorHandler(void) {

	while (1) {
	}

}
