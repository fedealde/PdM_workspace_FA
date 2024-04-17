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
	OK,
	BACK,
	PUMP
}FSMState_t;


void ScreenMain(void);
void ScreenDosageAsk(void);
void ScreenDosageError(void);
void ScreenUpdateDosage(void);
void ScreenUpdatePump(void);
void ScreenUpdateLevel(void);
void ScreenMainInfUpdate (void);
void FSMInit(void);
void FSMStateNew (FSMState_t stateNew);
void FSMStateRevert (void);
void FSMUpdate(void);




#endif /* API_INC_API_FSM_H_ */
