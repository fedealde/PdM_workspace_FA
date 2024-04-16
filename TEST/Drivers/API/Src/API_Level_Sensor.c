/*
 * API_Level_Sensor.c
 *
 *  Created on: Apr 15, 2024
 *      Author: flealu
 */
#include "API_Level_Sensor.h"

uint8_t alarm_level;

void LevelSensorSetAlarmLevel(uint8_t level) {

	alarm_level = level;

}

LevelSensorError LevelSensorGetAlarmLevel(void) {

	uint8_t level;

	if(LevelSensorGetCurrentLevel(&level) != true){return ALARM_ERROR;}

	if (level <= alarm_level) {
		return ALARM_ON;
	}

	return ALARM_OFF;

}

bool LevelSensorGetCurrentLevel(uint8_t* currentlevel) {

	uint32_t raw;
	float raw_accumulated;
	float K = (float)PERCENTAGE / (float) (ADC_SAMPLE * FILTER_SAMPLE_NUMBER);

	for (uint8_t i = 0; i < FILTER_SAMPLE_NUMBER; i++)

	{

		if (LevelSensorSense(&raw) != true) {
			return false;
		}

		raw_accumulated += raw;

	}


	*currentlevel = (uint8_t) (raw_accumulated * K);

	return true;

}

