/*
 * API_Level_Sensor.h
 *
 *  Created on: Apr 15, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_LEVEL_SENSOR_H_
#define API_INC_API_LEVEL_SENSOR_H_

#include "API_Level_Sensor_port.h"

#define FILTER_SAMPLE_NUMBER 50
#define ADC_SAMPLE 4096
#define PERCENTAGE 100

typedef enum {
	ALARM_ERROR = 0,
	ALARM_ON = 1,
	ALARM_OFF = 2
} LevelSensorError;

void LevelSensorSetAlarmLevel (uint8_t level);
LevelSensorError LevelSensorGetAlarmLevel (void);
bool LevelSensorGetCurrentLevel(uint8_t* currentlevel);

#endif /* API_INC_API_LEVEL_SENSOR_H_ */
