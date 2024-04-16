/*
 * API_Level_Sensor_port.h
 *
 *  Created on: Apr 15, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_LEVEL_SENSOR_PORT_H_
#define API_INC_API_LEVEL_SENSOR_PORT_H_

#include "API_ADC.h"

bool LevelSensorInit (void);
bool LevelSensorSense (uint32_t* value);


#endif /* API_INC_API_LEVEL_SENSOR_PORT_H_ */
