/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define TIME_BUTTON1 100
#define TIME_BUTTON2 500

tick_t def_tiem = TIME_BUTTON1;
delay_t led_delay =
		{ .startTime = 0, .duration = TIME_BUTTON1, .running = false };


/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */
	uint8_t level;
	uint32_t alarmlevel = 10;
	char buffer[20] = { 0 };



	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClockConfig();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	GPIOInit();

	//HAL_GPIO_WritePin(GPIOB, LD1_Pin | LD3_Pin | LD2_Pin, GPIO_PIN_SET);

	if(LevelSensorInit() != true){Error_Handler();}
	/* USER CODE BEGIN 2 */
	if(UARTInit()!=true){Error_Handler();}
	UARTSendString((uint8_t*)"ANDUVO LPM");
	LCDInit();
	LevelSensorSetAlarmLevel(alarmlevel);

	delayInit(&led_delay, def_tiem);
	debounceFSM_init();

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */
		switch (LevelSensorGetAlarmLevel()){

		case ALARM_ERROR: {

		UARTSendString((uint8_t*)"FFFF\n");
		break;

		}

		case ALARM_OFF: {

		UARTSendString((uint8_t*)"TODO JOYA PA\n");
		break;

		}

		case ALARM_ON: {

		UARTSendString((uint8_t*)"CORRE MAQUINA\n");
		break;

		}

		default: {

		UARTSendString((uint8_t*)"FFFF de DEFAULT\n");
		break;

		}


		}

		LevelSensorGetCurrentLevel(&level);
		HAL_Delay(50);
		//data = (uint8_t) ( (float)raw * (float) 100 / (float) 4095);
		LCDClear();
		if (level > 50) {
			LCDHome();
			LCDSendString((uint8_t*) "CARA DE TORTA FRITA");
			itoa(level, buffer, 10);
		} else {
			LCDHome();
			itoa(level, buffer, 10);
			LCDSendString((uint8_t*) buffer);
		}

		UARTSendString((uint8_t*)buffer);
		UARTSendString((uint8_t*)"\n");

		debounceFSM_update(); // The FSM is updated

		if (readKey()) {	//The blinking time is replased by the oposite

			if (led_delay.duration == TIME_BUTTON1) {

				delayWrite(&led_delay, TIME_BUTTON2);

			} else {
				delayWrite(&led_delay, TIME_BUTTON1);
			}

		}

		if (delayRead(&led_delay)) { // It is just waiting to toggle the led

			HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);

		}

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}


/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

