/*
 * API_debounce.c
 *
 *  Created on: Mar 24, 2024
 *      Author: flealu
 */

#include "API_debounce.h"

#define DEBOUNCE_DELAY 40

//Debounce states for the FSM
typedef enum {
	BUTTON_UP, BUTTON_FALLING, BUTTON_DOWN, BUTTON_RAISING,
} debounceState_t;

static bool_t button_state = false; // the real button state

static delay_t debounce_delay = { .startTime = 0, .duration = DEBOUNCE_DELAY,
		.running = false };
static debounceState_t debouce_state = BUTTON_UP;

bool_t readKey(void) { // this funktion will return the last button state

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

		if (BSP_PB_GetState(BUTTON_USER)) {

			debouce_state = BUTTON_FALLING;
			delayRead(&debounce_delay);
		}

		break;

	case BUTTON_FALLING: // Confirm the change

		if (delayRead(&debounce_delay)) {

			if (BSP_PB_GetState(BUTTON_USER) == true) {

				debouce_state = BUTTON_DOWN;
				button_state = true; //Change the variable that confirm the pressed button

			} else {

				debouce_state = BUTTON_UP;

			}

		}

		break;

	case BUTTON_DOWN: //It verifies if the button was released and change the state

		if (BSP_PB_GetState(BUTTON_USER) == false) {

			debouce_state = BUTTON_RAISING;
			delayRead(&debounce_delay);
		}

		break;

	case BUTTON_RAISING: // Confirm the change

		if (delayRead(&debounce_delay)) {

			if (BSP_PB_GetState(BUTTON_USER) == false) {

				debouce_state = BUTTON_UP;

			} else {

				debouce_state = BUTTON_DOWN;

			}

		}

		break;

	default: //If something went wrong, reset FSM and execute error handler

		debounceFSM_init();
		Error_Handler();

		break;

	}

}

void debounceFSM_init(void) { //initialize the FSM state

	debouce_state = BUTTON_UP;
	delayInit(&debounce_delay, DEBOUNCE_DELAY);
}

static void Error_Handler(void) {
	/* Turn LED2 on */
	BSP_LED_On(LED2);
	while (1) {
	}
}

