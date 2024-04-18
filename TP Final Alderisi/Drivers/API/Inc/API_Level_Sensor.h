/*
 * API_Level_Sensor.h
 *
 *  Created on: Apr 15, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_LEVEL_SENSOR_H_
#define API_INC_API_LEVEL_SENSOR_H_

#include "API_Level_Sensor_port.h"

/**
 * @brief Defines for Level Sensor
 *
 */
#define FILTER_SAMPLE_NUMBER 50
#define ADC_SAMPLE 4095
#define PERCENTAGE 100
#define ALARM_ACTIVATION_MAX_THRESHOLD 6
#define ALARM_ACTIVATION_MIN_THRESHOLD 3

/**
 * @brief Level sensor error typedef definition
 *
 */
typedef enum {
	ALARM_OFF = 0, ALARM_ON = 1, ALARM_ERROR = 2
} LevelSensorError_t;

/**
 * @brief Pump state typedef definition
 *
 */
typedef enum {
	PUMP_OFF = 0, PUMP_ON = 1,
} PumpState_t;

/**
 * @brief Set alarm function
 *
 */
void LevelSensorSetAlarm(void);
/**
 * @brief Reset alarm function
 *
 */
void LevelSensorResetAlarm(void);
/**
 * @brief Toggle sensor alarm
 *
 */
void LevelSensorToggleAlarm(void);

/**
 * @brief Level sensor initilization
 *
 * @return State of error, true if successful and false if error
 */
bool LevelSensorInit (void);

/**
 * @brief Function to get alarm level depending on the threshold level
 *
 * @param threshold
 * @return
 */
LevelSensorError_t LevelSensorGetAlarmLevel(uint8_t threshold);
/**
 * @brief Function to receive the level sensor from 0 to 100%
 *
 * @param currentlevel
 * @return
 */
bool LevelSensorGetCurrentLevel(uint8_t *currentlevel);
/**
 * @brief Set the pump
 *
 */
void PumpSet(void);
/**
 * @brief Reset the pump
 *
 */
void PumpReset(void);

#endif /* API_INC_API_LEVEL_SENSOR_H_ */
