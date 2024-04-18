/*
 * API_ADC.h
 *
 *  Created on: Apr 10, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_ADC_H_
#define API_INC_API_ADC_H_

//Includes
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_adc.h"

/**
 * @brief Initialize ADC
 *
 * @return Returns a handle for ADC
 */
ADC_HandleTypeDef* ADC1Init(void);

#endif /* API_INC_API_ADC_H_ */
