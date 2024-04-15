/*
 * API_ADC.c
 *
 *  Created on: Apr 10, 2024
 *      Author: flealu
 */

#include "API_ADC.h"

static void ADCErrorHandler(void);
extern ADC_HandleTypeDef hadc1;

bool ADC1_Init(void)
{

  ADC_ChannelConfTypeDef sConfig = {0};

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
	  ADCErrorHandler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
	  ADCErrorHandler();
  }

return true;

}


/**
* @brief ADC MSP Initialization
* This function configures the hardware resources used in this example
* @param hadc: ADC handle pointer
* @retval None
*/
bool ADCGPIOInit(ADC_HandleTypeDef* hadc)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  if(hadc->Instance==ADC1)
	  {
	  /* USER CODE BEGIN ADC1_MspInit 0 */

	  /* USER CODE END ADC1_MspInit 0 */
	    /* Peripheral clock enable */
	    __HAL_RCC_ADC1_CLK_ENABLE();

	    __HAL_RCC_GPIOA_CLK_ENABLE();
	    /**ADC1 GPIO Configuration
	    PA5     ------> ADC1_IN5
	    */
	    GPIO_InitStruct.Pin = GPIO_PIN_5;
	    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    return true;

  }

  return false;

}

/**
* @brief ADC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hadc: ADC handle pointer
* @retval None
*/
bool ADCGPIODeInit(ADC_HandleTypeDef* hadc)
{
  if(hadc->Instance==ADC1)
  {
	    __HAL_RCC_ADC1_CLK_DISABLE();

	    /**ADC1 GPIO Configuration
	    PA5     ------> ADC1_IN5
	    */
	    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5);

    return true;

  }

  return false;

}




static void ADCErrorHandler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {

  }
  /* USER CODE END Error_Handler_Debug */
}
