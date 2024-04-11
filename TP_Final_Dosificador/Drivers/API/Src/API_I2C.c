/*
 * API_I2C.c
 *
 *  Created on: Apr 4, 2024
 *      Author: flealu
 */

#include "API_I2C.h"

/*The handler for I2C is created*/
I2C_HandleTypeDef hi2c1;


bool I2C1Init(void){

	/*GPIO for I2C configuration is created*/
	GPIO_InitTypeDef GPIO_InitStruct;

	/*Handler is filled with standard configuration*/
	hi2c1.Instance = I2C1;

	hi2c1.Init.ClockSpeed = 10000;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	/* GPIO Port B Clock Enable - This will enable RCC CLK for the port B, where I2C1 is found*/
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*GPIO for I2C configuration is filled*/
	GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9; /*IN PB_8 is SCL and PIN PB_9 is SDA (CN7 header)*/
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;/*This means Alternate Function Open Drain*/
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;/*This specifies the peripheral instance, in this case, for I2C1*/

	/*The GPIO is initialized to be used for I2C - it is void function*/
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	 /* Peripheral clock enable - This will enable I2C1 clock for the peripheral*/
	__HAL_RCC_I2C1_CLK_ENABLE();

	/*This initialize the peripheral I2C as I2C1*/
	if(HAL_I2C_Init(&hi2c1) != HAL_OK){
		return false;
	}

	return true;

}


