/*
 * API_FSM.h
 *
 *  Created on: Apr 16, 2024
 *      Author: flealu
 */

#ifndef API_INC_API_FSM_H_
#define API_INC_API_FSM_H_

#include "stm32f4xx_hal.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "API_LCD.h"
#include "API_Level_Sensor.h"
#include "API_UART.h"
#include "API_GPIO.h"
#include "API_SystemClock.h"
#include "API_Delay.h"
#include "API_Debounce.h"
#include "API_Keypad.h"

typedef enum {

	IDLE = 0,
	DOSAGE_1,
	DOSAGE_2,
	DOSAGE_3,
	DOSAGE_4,
	DOSAGE_ASK,
	DOSAGE_VERIF,
	BACK,
	PUMP
} FSMState_t;

void ScreenMain(void);
void ScreenDosageAsk(void);
void ScreenDosageError(void);
void ScreenUpdateDosage(void);
void ScreenUpdatePump(void);
void ScreenUpdateLevel(void);
void ScreenMainInfUpdate(void);
void ScreenDosageInfUpdate(FSMState_t fromDosageNumber);
void FSMInit(void);
void FSMStateNew(FSMState_t stateNew);
void FSMStateRevert(void);
bool FSMIsNumber(char keyIsNumber);
void FSMUpdate(void);
void AlarmUpdate(void);

#define DOSAGE_CANT_CHAR 5
#define ALARM_DELAY_DURATION 500
#define ALARM_UART_MAX_DELAY_DURATION 5000
#define ALARM_UART_MIN_DELAY_DURATION 2000
#define LCD_WIDTH 20

#endif /* API_INC_API_FSM_H_ */
