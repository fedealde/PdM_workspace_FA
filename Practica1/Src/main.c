/**
 ******************************************************************************
 * @file    UART/UART_Printf/Src/main.c
 * @author  MCD Application Team
 * @brief   This example shows how to retarget the C library printf function
 *          to the UART.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdint.h"

/** @addtogroup STM32F4xx_HAL_Examples
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define led_cant 3
#define index ((led_cant*2) - 1)
#define delay 200
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void) {
	/* STM32F4xx HAL library initialization:
	 - Configure the Flash prefetch
	 - Systick timer is configured by default as source of time base, but user
	 can eventually implement his proper time base source (a general purpose
	 timer for example or other time source), keeping in mind that Time base
	 duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
	 handled in milliseconds basis.
	 - Set NVIC Group Priority to 4
	 - Low Level Initialization
	 */
	HAL_Init();

	/* Configure the system clock to 180 MHz */
	SystemClock_Config();

	/* Initialize BSP Led for LED1 */
	BSP_LED_Init(LED1);
	/* Initialize BSP Led for LED2 */
	BSP_LED_Init(LED2);
	/* Initialize BSP Led for LED3 */
	BSP_LED_Init(LED3);
	/* Initialize BSP PB for BUTTON_USER */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	int state = 0, button_state_before = 0, led_array[led_cant], s = 0, j = 0,
			k = 0;

	led_array[0] = LED1;
	led_array[1] = LED2;
	led_array[2] = LED3;

	/* Infinite loop */
	while (1) {

		//Detecto si hubo flanco ascendente y guardo flag
		if ((BSP_PB_GetState(BUTTON_USER) != 0) && button_state_before == 0) {

			button_state_before = 1;

		}

		//Si hubo flanco descendente (es porque antes hubo ascendete), reinicio
		//bansdera y cambio de estado al estado anterior
		if ((BSP_PB_GetState(BUTTON_USER) != 1) && button_state_before == 1) {

			//state es igual al state negado, y le pongo una mascara de
			//un bit, porque sino state valdria o 0xFF o 0x00, y necesitamos
			//0x00 o 0x01
			state = ((~state) & ((int) 1));
			button_state_before = 0;

		}

		//Este código primero define los parámetros del for y del indice del vector, para luego
		//ejecutar unicamente un solo for() con distinto indice

		if (state) {

			j = 0;
			k = index;
			s = 1;

		} else {

			j = -index;
			k = 0;
			s = -1;

		}

		for (int i = j; i <= k; i++) {
			BSP_LED_Toggle(led_array[(i * s / 2)]);
			HAL_Delay(delay);
		}



		/*

		 //Depende del estado hace una secuencia u otra, utilizando un vector de leds


		 if (state) {

		 for (i = 0; i <= led_cant*2-1; i++) {
		 BSP_LED_Toggle(led_array[i/2]);
		 HAL_Delay(delay);
		 }

		 } else {

		 for (i = led_cant*2-1; i >= 0; i--) {
		 BSP_LED_Toggle(led_array[i/2]);
		 HAL_Delay(delay);
		 }

		 }

		 */

		/*

//Este código es el más sencillo y solo se basa en generar la secuencia
		 if (state) {

		 //Enciende y apaga LED1
		 BSP_LED_On(LED1);
		 HAL_Delay(200);
		 BSP_LED_Off(LED1);
		 HAL_Delay(200);
		 //Enciende y apaga LED2
		 BSP_LED_On(LED2);
		 HAL_Delay(200);
		 BSP_LED_Off(LED2);
		 HAL_Delay(200);
		 //Enciende y apaga LED3
		 BSP_LED_On(LED3);
		 HAL_Delay(200);
		 BSP_LED_Off(LED3);
		 HAL_Delay(200);

		 } else {
		 //Enciende y apaga LED3
		 BSP_LED_On(LED3);
		 HAL_Delay(200);
		 BSP_LED_Off(LED3);
		 HAL_Delay(200);
		 //Enciende y apaga LED2
		 BSP_LED_On(LED2);
		 HAL_Delay(200);
		 BSP_LED_Off(LED2);
		 HAL_Delay(200);
		 //Enciende y apaga LED1
		 BSP_LED_On(LED1);
		 HAL_Delay(200);
		 BSP_LED_Off(LED1);
		 HAL_Delay(200);

		 }
		 */

	}
}

static void SystemClock_Config(void) {
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();

	/* The voltage scaling allows optimizing the power consumption when the device is
	 clocked below the maximum system frequency, to update the voltage scaling value
	 regarding system frequency refer to product datasheet.  */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 360;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}

	if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}
}
/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void) {
	/* Turn LED2 on */
	BSP_LED_On(LED2);
	while (1) {
	}
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
