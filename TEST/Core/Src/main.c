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

	char a = '\0';
	uint8_t level;
	char buffer[20] = { 0 };

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

	LCDPosition(2, 2);
	LCDSendString((uint8_t*)"HOLA");

	while (1) {

		a = KeypadDebounceFSMUpdate();
		LCDHome();
		if(a!='\0')LCDSendData(a);

		LCDPosition(0, 3);
		LevelSensorGetCurrentLevel(&level);
		itoa(level, buffer, 10);
		LCDSendString((uint8_t*) buffer);
		UARTSendString((uint8_t*) buffer);
		UARTSendString((uint8_t*) "\n");
		for(uint8_t i=0; i<20; i++)
		{buffer[i]=' ';}
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
