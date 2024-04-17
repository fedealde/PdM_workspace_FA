/*
 * API_Keypad.c
 *
 *  Created on: Apr 15, 2024
 *      Author: flealu
 */

#include "API_Keypad.h"
#include "API_Keypad_port.h"
#include "API_Delay.h"
#include "API_GPIO.h"

static void KeypadDebounceErrorHandler(void);

#define KEYPAD_DEB_DELAY 40

extern const uint16_t COLS_PINS_ARRAY[];
extern GPIO_TypeDef * COLS_PORTS_ARRAY[];

extern const uint16_t ROWS_PINS_ARRAY[];
extern GPIO_TypeDef * ROWS_PORTS_ARRAY[];

char KeypadChars[] = {
'1', '2', '3', 'U',
'4', '5', '6', 'K',
'7', '8', '9', 'W',
'P', '0', 'D', 'B',
};

typedef enum {
	KEYPAD_SCAN, KEY_DETECTED, KEY_PRESSED, KEY_RELEASED,
} KeypadDebounceState_t;

static delay_t keypad_debounce_delay = { .startTime = 0, .duration = KEYPAD_DEB_DELAY,
		.running = false };

static KeypadDebounceState_t keypad_debouce_state = KEYPAD_SCAN;

void KeypadInit(void){

	KeypadPortGPIOInit();

	for(uint8_t i=0; i<NUM_OF_ROWS; i++ ){

		KeypadPortPinWrite(ROWS_PORTS_ARRAY[i], ROWS_PINS_ARRAY[i], 0);

	}

}

char KeypadScan(void) {

	uint8_t row = 0;
	uint8_t col = 0;
	uint8_t i = 0;

	for (row = 0; row < NUM_OF_ROWS; row++) {

		for (i = 0; i < NUM_OF_ROWS; i++) {
			KeypadPortPinWrite(ROWS_PORTS_ARRAY[i], ROWS_PINS_ARRAY[i], ON);
		}

		KeypadPortPinWrite(ROWS_PORTS_ARRAY[row], ROWS_PINS_ARRAY[row], OFF);

		for (col = 0; col < NUM_OF_COLS; col++) {

			if (KeypadPortPinRead(COLS_PORTS_ARRAY[col], COLS_PINS_ARRAY[col]) == OFF) {
				return KeypadChars[row * NUM_OF_ROWS + col];
			}
		}
	}

	return '\0';

}


char KeypadDebounceFSMUpdate(void) {

	char key_detected = '\0';
	char key_pressed = '\0';
	static char key_last_pressed = '\0';

	switch (keypad_debouce_state) {

	case KEYPAD_SCAN: //It verifies if the button was pressed and change the state

		key_detected = KeypadScan();

		if (key_detected != '\0') {

			key_last_pressed = key_detected;
			keypad_debouce_state = KEY_DETECTED;
			delayRead(&keypad_debounce_delay);
		}

		break;

	case KEY_DETECTED: // Confirm the change

		if (delayRead(&keypad_debounce_delay)) {

			key_detected = KeypadScan();

			if (key_detected == key_last_pressed) {

				keypad_debouce_state = KEY_PRESSED;

			} else {

				keypad_debouce_state = KEYPAD_SCAN;

			}

		}

		break;

	case KEY_PRESSED: //It verifies if the button was released and change the state

		key_detected = KeypadScan();

		if (key_detected != key_last_pressed) {

			if(key_detected == '\0'){

				key_pressed = key_last_pressed;

			}

			keypad_debouce_state = KEY_RELEASED;
			delayRead(&keypad_debounce_delay);
		}



		break;

	case KEY_RELEASED: // Confirm the change

		if (delayRead(&keypad_debounce_delay)) {

			key_detected = KeypadScan();

			if (key_detected == '\0') {


				keypad_debouce_state = KEYPAD_SCAN;

			} else {

				if (key_detected == key_last_pressed){

					keypad_debouce_state = KEY_PRESSED;

				} else {

					keypad_debouce_state = KEYPAD_SCAN;

				}

			}

		}

		break;

	default: //If something went wrong, reset FSM and execute error handler

		KeypadDebounceFSMInit();
		KeypadDebounceErrorHandler();

		break;

	}

	return key_pressed;

}



void KeypadDebounceFSMInit(void) { //initialize the FSM state

	keypad_debouce_state = KEYPAD_SCAN;
	delayInit(&keypad_debounce_delay, KEYPAD_DEB_DELAY);
}


static void KeypadDebounceErrorHandler(void) {
	/* Turn LED_RED on */
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, ON);
	while (1) {
	}
}


