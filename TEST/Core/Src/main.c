/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 */

#include "main.h"

#define TIME_BUTTON1 100
#define TIME_BUTTON2 500

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

	HAL_Init();

	SystemClockConfig();

	GPIOInit();
	if (LevelSensorInit() != true) {
		Error_Handler();
	}
	if (UARTInit() != true) {
		Error_Handler();
	}
	if (LCDInit() != true) {
		Error_Handler();
	}

	KeypadInit();
	KeypadDebounceFSMInit();

	LCDClear();
	ScreenMain();
	FSMInit();

	while (1) {


		FSMUpdate();





	}

}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {

	__disable_irq();
	while (1) {
	}

}
