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

bool LevelSensorInit(void);
bool LevelSensorSense(uint32_t *value);
void AlarmPortPinWrite(GPIO_PinState State);
void PumpPortPinWrite(GPIO_PinState State);
void LevelSensorAlarmPortToggle(void);

#endif /* API_INC_API_LEVEL_SENSOR_PORT_H_ */
