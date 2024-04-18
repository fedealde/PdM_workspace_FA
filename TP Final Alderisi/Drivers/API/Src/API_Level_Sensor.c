/*
 * API_Level_Sensor.c
 *
 *  Created on: Apr 15, 2024
 *      Author: flealu
 */
#include "API_Level_Sensor.h"
#include <math.h>

void LevelSensorSetAlarm(void) {

	AlarmPortPinWrite(ALARM_ON);

}

void LevelSensorResetAlarm(void) {

	AlarmPortPinWrite(ALARM_OFF);

}

void PumpSet(void) {

	PumpPortPinWrite(PUMP_ON);

}

void PumpReset(void) {

	PumpPortPinWrite(PUMP_OFF);

}

void LevelSensorToggleAlarm(void) {

	LevelSensorAlarmPortToggle();

}

LevelSensorError_t LevelSensorGetAlarmLevel(uint8_t threshold) {

	uint8_t level;

	if (LevelSensorGetCurrentLevel(&level) != true) {
		return ALARM_ERROR;
	}

	if (level <= threshold) {
		return ALARM_ON;
	}

	return ALARM_OFF;

}

bool LevelSensorGetCurrentLevel(uint8_t *currentlevel) {

	uint32_t raw;
	float raw_accumulated;
	float K = (float) PERCENTAGE / (float) (ADC_SAMPLE * FILTER_SAMPLE_NUMBER);

	for (uint8_t i = 0; i < FILTER_SAMPLE_NUMBER; i++)

	{

		if (LevelSensorSense(&raw) != true) {
			return false;
		}

		raw_accumulated += (raw);

	}

	*currentlevel = (uint8_t) round((raw_accumulated * K));

	return true;

}

