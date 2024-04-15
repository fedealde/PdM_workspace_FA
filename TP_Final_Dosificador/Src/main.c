/**
 ******************************************************************************
 * @file    Practica4_1/Src/main.c
 * @author  Federico Alderisi
 * @brief   This program was made for CESE, PdM, Practica4_1
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_delay.h"
#include "API_debounce.h"
#include "API_uart.h"
#include "API_ADC.h"




/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TIME_BUTTON1 100
#define TIME_BUTTON2 500
#define RX_BUFFER_SIZE 20
#define NUM_SAMPLES 10 // Número de muestras para promediar
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/*General definitions like LED, delay structures, stateFSM*/

const Led_TypeDef led = LED_GREEN;
tick_t def_tiem = TIME_BUTTON1;
delay_t led_delay =
		{ .startTime = 0, .duration = TIME_BUTTON1, .running = false };
//definitions for receiving code
uint8_t stringRecived [RX_BUFFER_SIZE] = {0};
const uint16_t sizeRecived = RX_BUFFER_SIZE;


uint16_t adc_value; // Variable para almacenar el valor del ADC
uint16_t adc_sum = 0; // Suma acumulada de las muestras
uint16_t adc_average; // Promedio de las muestras

ADC_HandleTypeDef hadc1 = {0};

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
	  __HAL_RCC_SYSCFG_CLK_ENABLE();
	  __HAL_RCC_PWR_CLK_ENABLE();
	/* Configure the system clock to 180 MHz */
	SystemClock_Config();

	/* Initialize BSP for LED, BUTTON_USER; delay and FSM */

	BSP_LED_Init(LED_BLUE);
	BSP_LED_Init(LED_RED);
	BSP_LED_Init(LED_GREEN);
/*
	delayInit(&led_delay, def_tiem);

	uartInit();
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
	debounceFSM_init();

	uartSendString((uint8_t *) "\nWHILE BEGINING\n\0");
*/

	ADC1_Init();
	ADCGPIOInit(&hadc1);

//	if(LCDInit()!=true){BSP_LED_On(LED_RED);}
	uint32_t raw;


	/* Infinite loop */
	while (1) {

/*		debounceFSM_update(); // The FSM is updated

		if (readKey()) {	//The blinking time is replased by the oposite

			if (led_delay.duration == TIME_BUTTON1) {

				delayWrite(&led_delay, TIME_BUTTON2);

			} else {
				delayWrite(&led_delay, TIME_BUTTON1);
			}

		}

		if (delayRead(&led_delay)) { // It is just waiting to toggle the led

			BSP_LED_Toggle(led);

		}

		//it checks if there where a rising or fallin edge and notify through uart
		if(readFallingEdge()){uartSendString((uint8_t*)"Falling Edge Detected\n\0");}

		if(readRisingEdge()){uartSendString((uint8_t*)"Rising Edge Detected\n\0");}



		//----------------RECIVE CODE EXAMPLE - LOOPBACK---------------

		uartReceiveStringSize(stringRecived, sizeRecived);//it receive msg from uart's computer

		if(stringRecived[0] != 0){ //to print only if there is something different to NULL (0)

			uartSendString((uint8_t *) "LookBack : \0");
			uartSendString(stringRecived); //print again from stm to computer until NULL is found
			uartSendString((uint8_t *) "\n\0");

			for(uint8_t i = 0; i < sizeRecived; i++) stringRecived[i] = 0; //ensure to have NULL, to "clean" the buffer

		}

		//To send msg from CuteCom fluently, input should be ASCII with "None" in box "command end line", delay = 0 ms

		//----------------RECIVE CODE EXAMPLE - LOOPBACK---------------

*/
	    HAL_ADC_Start(&hadc1);
	    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	    raw = HAL_ADC_GetValue(&hadc1);
	    HAL_Delay(100);





	}




}

static void SystemClock_Config(void) {
	 RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	  /** Configure the main internal regulator output voltage
	  */
	  __HAL_RCC_PWR_CLK_ENABLE();
	  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	  /** Initializes the RCC Oscillators according to the specified parameters
	  * in the RCC_OscInitTypeDef structure.
	  */
	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	  RCC_OscInitStruct.PLL.PLLM = 4;
	  RCC_OscInitStruct.PLL.PLLN = 168;
	  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	  RCC_OscInitStruct.PLL.PLLQ = 7;
	  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  /** Initializes the CPU, AHB and APB buses clocks
	  */
	  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	  {
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
	BSP_LED_On(LED_RED);
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

