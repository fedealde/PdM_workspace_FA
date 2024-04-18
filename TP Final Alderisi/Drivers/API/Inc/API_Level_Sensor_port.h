/*
 * API_Level_Sensor_port.h
 *
 *  Created on: Apr 15, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_LEVEL_SENSOR_PORT_H_
#define API_INC_API_LEVEL_SENSOR_PORT_H_

#include "API_ADC.h"
#include "API_GPIO.h"

/**
 * @brief Initialize level sensor
 *
 * @return True if successful and false if error
 */
bool LevelSensorPortInit(void);
/**
 * @brief Sense of level from ADC
 *
 * @param value
 * @return True if successful and false if error
 */
bool LevelSensorPortSense(uint32_t *value);
/**
 * @brief Write the alarm pin
 *
 * @param State
 */
void AlarmPortPinWrite(GPIO_PinState State);
/**
 * @brief Write the pump pin
 *
 * @param State
 */
void PumpPortPinWrite(GPIO_PinState State);
/**
 * @brief Toggle the alarm pin
 *
 */
void LevelSensorAlarmPortToggle(void);

#endif /* API_INC_API_LEVEL_SENSOR_PORT_H_ */
