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
#define ADC_SAMPLE 4095
#define PERCENTAGE 100
#define ALARM_ACTIVATION_MAX_THRESHOLD 6
#define ALARM_ACTIVATION_MIN_THRESHOLD 3

typedef enum {
	ALARM_OFF = 0, ALARM_ON = 1, ALARM_ERROR = 2
} LevelSensorError_t;

typedef enum {
	PUMP_OFF = 0, PUMP_ON = 1,
} PumpState_t;

void LevelSensorSetAlarm(void);
void LevelSensorResetAlarm(void);
void LevelSensorToggleAlarm(void);
LevelSensorError_t LevelSensorGetAlarmLevel(uint8_t threshold);
bool LevelSensorGetCurrentLevel(uint8_t *currentlevel);
void PumpSet(void);
void PumpReset(void);

#endif /* API_INC_API_LEVEL_SENSOR_H_ */
