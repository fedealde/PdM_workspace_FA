/*
 * API_debounce.c
 *
 *  Created on: Mar 24, 2024
 *      Author: flealu
 */

#include "API_Debounce.h"

static void DebounceErrorHandler(void);

#define DEBOUNCE_DELAY 40

/**
 * @brief Set the rising variable to be read from outside
 *
 */
static void setRisingEdge (void);
/**
 * @brief Set the falling variable to be read from outside
 *
 */
static void setFallingEdge (void);

//Debounce states for the FSM
typedef enum {
	BUTTON_UP, BUTTON_FALLING, BUTTON_DOWN, BUTTON_RAISING,
} debounceState_t;

static bool_t button_state = false; // the real button state

static delay_t debounce_delay = { .startTime = 0, .duration = DEBOUNCE_DELAY,
		.running = false };
static debounceState_t debouce_state = BUTTON_UP;

//status variables
static bool_t statusFallingEdge;
static bool_t statusRisingEdge;

bool_t readKey(void) { // this function will return the last button state

	if (button_state) {
		button_state = false; //To reset the state. it is taken just the real change or value one time
		//otherwise it could repeat the action taken after measuring in the main task
		return true;
	}

	return false;

}

void debounceFSM_update(void) {

	switch (debouce_state) {

	case BUTTON_UP: //It verifies if the button was pressed and change the state

		if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port ,USER_Btn_Pin)) {

			debouce_state = BUTTON_FALLING;
			setFallingEdge();
			delayRead(&debounce_delay);
		}

		break;

	case BUTTON_FALLING: // Confirm the change

		if (delayRead(&debounce_delay)) {

			if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port ,USER_Btn_Pin) == true) {

				debouce_state = BUTTON_DOWN;
				button_state = true; //Change the variable that confirm the pressed button

			} else {

				debouce_state = BUTTON_UP;

			}

		}

		break;

	case BUTTON_DOWN: //It verifies if the button was released and change the state

		if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port ,USER_Btn_Pin) == false) {

			debouce_state = BUTTON_RAISING;
			setRisingEdge();
			delayRead(&debounce_delay);
		}

		break;

	case BUTTON_RAISING: // Confirm the change

		if (delayRead(&debounce_delay)) {

			if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port ,USER_Btn_Pin) == false) {

				debouce_state = BUTTON_UP;

			} else {

				debouce_state = BUTTON_DOWN;

			}

		}

		break;

	default: //If something went wrong, reset FSM and execute error handler

		debounceFSM_init();
		DebounceErrorHandler();

		break;

	}

}

void debounceFSM_init(void) { //initialize the FSM state

	debouce_state = BUTTON_UP;
	delayInit(&debounce_delay, DEBOUNCE_DELAY);
}

bool_t readRisingEdge (void){

	bool_t state = statusRisingEdge;

	if(statusRisingEdge)
	{
		statusRisingEdge = false;
	}

	return state;

}

bool_t readFallingEdge (void){

	bool_t state = statusFallingEdge;

	if(statusFallingEdge)
	{
		statusFallingEdge = false;
	}

	return state;

}


static void setRisingEdge (void){

		statusRisingEdge = true;

}

static void setFallingEdge (void){

		statusFallingEdge = true;
}



static void DebounceErrorHandler(void) {
	/* Turn LED_RED on */
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
	while (1) {
	}
}

