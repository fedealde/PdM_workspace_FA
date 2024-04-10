/*
 * API_LCD_port.c
 *
 *  Created on: Apr 4, 2024
 *      Author: flealu
 */

#include "API_LCD_port.h"
#include "stm32f4xx_nucleo_144.h"

extern I2C_HandleTypeDef hi2c1;

bool LCDPortInit (void)
{
	return I2C1Init();
}


bool LCDPortSendByte(uint8_t data){

if(HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD_SHIFTED,&data,sizeof(data),LCD_SEND_DELAY) != HAL_OK){
	return false;
}

return true;

}

void LCDPortDelay (uint32_t delay){

	HAL_Delay(delay);

}

void LCDPortErrorHandler(void) {

	BSP_LED_Init(LED_RED);
	/* Turn LED_RED on */
	BSP_LED_On(LED_RED);
	while (1) {
	}

}
