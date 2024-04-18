/*
 * API_GPIO.h
 *
 *  Created on: Apr 15, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_GPIO_H_
#define API_INC_API_GPIO_H_

// Includes
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>
/**
 * @brief GPIOs Initialization
 *
 */
void GPIOInit(void);

//Defines for GPIOs and ports
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB
#define ALARM_Pin GPIO_PIN_15
#define ALARM_Port GPIOE
#define PUMP_Pin GPIO_PIN_14
#define PUMP_Port GPIOE

#endif /* API_INC_API_GPIO_H_ */
