/**
 ******************************************************************************
 * @author			: Alderisi Federico
 * @file			: main.c
 * @brief			: Main program
 * @attention		: This program was made based on auto-generation code
 * 						provided for STM32CubeIDE MX - To compile, the
 * 						auto-generating code must be OFF *
 ******************************************************************************
 */

#include "main.h"

/**
 * @brief  The application entry point.
 * @retval int
 */

int main(void) {

	//Initialization funtions

	if( HAL_Init() != HAL_OK) {
		Error_Handler();
	}

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

	//While loop
	while (1) {

		//Updato of FSM
		FSMUpdate();

		//Update of Alarm Sensor Level
		AlarmUpdate();

	}

	return 0;
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
