/*
 * API_ADC.h
 *
 *  Created on: Apr 10, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_ADC_H_
#define API_INC_API_ADC_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_adc.h"


bool ADC1_Init(void);
bool ADCGPIOInit(ADC_HandleTypeDef* hadc);
bool ADCGPIODeInit(ADC_HandleTypeDef* hadc);



#endif /* API_INC_API_ADC_H_ */
