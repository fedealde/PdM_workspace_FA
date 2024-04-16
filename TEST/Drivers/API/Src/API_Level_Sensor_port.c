/*
 * API_Level_Sensor_port.c
 *
 *  Created on: Apr 15, 2024
 *      Author: flealu
 */

#include "API_Level_Sensor_port.h"


static ADC_HandleTypeDef* handler = NULL;

bool LevelSensorInit (void)
{

	handler = ADC1Init();

	if(handler == NULL)
	{
		return false;
	}

	return true;

}

 bool LevelSensorSense (uint32_t* value)
{


	if(HAL_ADC_Start(handler) == HAL_OK)
	{

	if(HAL_ADC_PollForConversion(handler, HAL_MAX_DELAY) == HAL_OK)
	{

	*value = HAL_ADC_GetValue(handler);
	return true;

	}

	}

	return false;

}
