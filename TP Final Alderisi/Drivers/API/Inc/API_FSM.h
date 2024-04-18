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

//Definitions for FSM
#define DOSAGE_CANT_CHAR 5
#define ALARM_DELAY_DURATION 500
#define ALARM_UART_MAX_DELAY_DURATION 5000
#define ALARM_UART_MIN_DELAY_DURATION 2000
#define LCD_WIDTH 20

/**
 * @brief  FSMState_t typedef definition. Used for FSM states
 *
 */
typedef enum {

	IDLE = 0,    /**< IDLE Where the FSM wait and show information*/
	DOSAGE_1,    /**< DOSAGE_1 First entry for dosage*/
	DOSAGE_2,    /**< DOSAGE_2 Second entry for dosage*/
	DOSAGE_3,    /**< DOSAGE_3 Third entry for dosage*/
	DOSAGE_4,    /**< DOSAGE_4 Fourth entry for dosage*/
	DOSAGE_ASK,  /**< DOSAGE_ASK Ask for change dosage*/
	DOSAGE_VERIF,/**< DOSAGE_VERIF Verification of dosage*/
	BACK,        /**< BACK Back to IDLE*/
	PUMP         /**< PUMP Change Pump state*/
} FSMState_t;

/**
 * @brief Print main screen
 *
 */
void ScreenMain(void);
/**
 * @brief Print ask for dosage
 *
 */
void ScreenDosageAsk(void);
/**
 * @brief Print error dosage
 *
 */
void ScreenDosageError(void);
/**
 * @brief Update dosage on screen
 *
 */
void ScreenUpdateDosage(void);
/**
 * @brief Update pump state on screen
 *
 */
void ScreenUpdatePump(void);
/**
 * @brief Update level on screen
 *
 */
void ScreenUpdateLevel(void);
/**
 * @brief Update main information on screen
 *
 */
void ScreenMainInfUpdate(void);
/**
 * @brief Update dosage information on screen
 *
 * @param fromDosageNumber
 */
void ScreenDosageInfUpdate(FSMState_t fromDosageNumber);
/**
 * @brief Initialize FSM
 *
 */
void FSMInit(void);
/**
 * @brief Change the state of FSM
 *
 * @param stateNew
 */
void FSMStateNew(FSMState_t stateNew);
/**
 * @brief Reverse the direction of FSM, return to last FSM state
 *
 */
void FSMStateRevert(void);
/**
 * @brief
 *
 * @param keyIsNumber
 * @return Determine if key is a number
 */
bool FSMIsNumber(char keyIsNumber);
/**
 * @brief Update FSM state
 *
 */
void FSMUpdate(void);
/**
 * @brief Update alarm state
 *
 */
void AlarmUpdate(void);



#endif /* API_INC_API_FSM_H_ */
