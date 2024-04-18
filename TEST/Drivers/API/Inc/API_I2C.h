/*
 * API_I2C.h
 *
 *  Created on: Apr 4, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_I2C_H_
#define API_INC_API_I2C_H_

#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"

/**
 * @brief Initialize I2C1
 *
 * @return true if ok, or false in case of error
 */
bool I2C1Init(void);

#endif /* API_INC_API_I2C_H_ */
