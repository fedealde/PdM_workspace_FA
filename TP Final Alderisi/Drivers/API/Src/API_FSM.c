/*
 * API_FSM.c
 *
 *  Created on: Apr 16, 2024
 *      Author: flealu
 */

#include "API_FSM.h"

const uint16_t DOSAGE_MIN_VALUE = 300;
const uint16_t DOSAGE_MAX_VALUE = 3000;

uint16_t dosageInt = 300;
uint16_t dosageLast = 300;
uint16_t dosageAux = 0;

uint8_t levelInt = 0;
uint8_t levelIntLast = 0;

char dosageCharVector[DOSAGE_CANT_CHAR] = { 0 };

char dosageScreenString[LCD_WIDTH] = { 0 };
char levelScreenString[LCD_WIDTH] = { 0 };

char key = '\0';
const char one = '1', two = '2', three = '3', four = '4', five = '5', six = '6',
		seven = '7', eight = '8', nine = '9', zero = '0', up = 'U', down = 'W',
		ok = 'K', back = 'B', dosage = 'D', pump = 'P', empty = '\0';

bool pumpState = 0, pumpFlagAlarm = 0;
bool pumpStateLast = 0;

FSMState_t stateCurrent = IDLE, stateLast = IDLE;

delay_t delayAlarm = { 0 }, delayAlarmMin = { 0 }, delayAlarmMax = { 0 };

void ScreenTemplate(void) {

	LCDHome();
	LCDSendString((uint8_t*) "     DOSIFICADOR    ");

	LCDPosition(0, 1);
	LCDSendString((uint8_t*) "DOSIS:      mL/min  ");

	LCDPosition(0, 2);
	LCDSendString((uint8_t*) "BOMBA:              ");

	LCDPosition(0, 3);
	LCDSendString((uint8_t*) "NIVEL:    %         ");

}

void ScreenMain(void) {

	LCDBlinkOff();
	ScreenTemplate();
	ScreenUpdateDosage();
	ScreenUpdatePump();
	ScreenUpdateLevel();

}

void ScreenUpdateDosage(void) {

	LCDPosition(7, 1);
	sprintf(dosageScreenString, "%4d", dosageInt);
	LCDSendString((uint8_t*) dosageScreenString);

}

void ScreenUpdatePump(void) {

	LCDPosition(0, 2);
	if (pumpState) {
		LCDSendString((uint8_t*) "BOMBA: ON           ");

	} else {
		LCDSendString((uint8_t*) "BOMBA: OFF          ");
	}
}

void ScreenUpdateLevel(void) {

	LCDPosition(7, 3);
	LevelSensorGetCurrentLevel(&levelInt);
	sprintf(levelScreenString, "%3d", levelInt);
	LCDSendString((uint8_t*) levelScreenString);

}

void ScreenDosageAsk(void) {

	LCDHome();
	LCDSendString((uint8_t*) "     DOSIFICADOR    ");
	LCDPosition(0, 1);
	LCDSendString((uint8_t*) "DOSIS:      mL/min  ");
	LCDPosition(0, 2);
	LCDSendString((uint8_t*) "  CONFIRMAR DOSIS?  ");
	LCDPosition(0, 3);
	LCDSendString((uint8_t*) "SI            VOLVER");

}

void ScreenDosageError(void) {

	uint8_t screenRange[20];
	sprintf((char*) screenRange, "VALOR >=%d Y <=%d   ", DOSAGE_MIN_VALUE,
			DOSAGE_MAX_VALUE);
	LCDHome();
	LCDSendString((uint8_t*) screenRange);
	LCDPosition(0, 1);
	LCDSendString((uint8_t*) "DOSIS:      mL/min  ");
	ScreenUpdatePump();
	LCDPosition(0, 3);
	LCDSendString((uint8_t*) "NIVEL:    %         ");
	ScreenUpdateLevel();
	LCDPosition(7, 1);
	LCDBlinkOn();

}

void ScreenMainInfUpdate(void) {

	LevelSensorGetCurrentLevel(&levelInt);

	if (dosageInt != dosageLast) {
		ScreenUpdateDosage();
		dosageLast = dosageInt;
	}
	if (pumpState != pumpStateLast) {
		ScreenUpdatePump();
		pumpStateLast = pumpState;
	}
	if (levelInt != levelIntLast) {
		ScreenUpdateLevel();
		levelIntLast = levelInt;
	}

}

void ScreenDosageInfUpdate(FSMState_t fromDosageNumber) {

	LevelSensorGetCurrentLevel(&levelInt);

	if (pumpState != pumpStateLast) {
		ScreenUpdatePump();
		pumpStateLast = pumpState;
		LCDPosition(7 + (fromDosageNumber - 1), 1);
	}
	if (levelInt != levelIntLast) {
		ScreenUpdateLevel();
		levelIntLast = levelInt;
		LCDPosition(7 + (fromDosageNumber - 1), 1);
	}

}

void FSMInit(void) {

	stateCurrent = IDLE;
	key = '\0';
	pumpFlagAlarm = 0;
	pumpState = 0;
	pumpStateLast = 0;
	dosageInt = 300;
	dosageLast = 300;
	dosageAux = 0;
	stateCurrent = IDLE;
	stateLast = IDLE;
	levelInt = 0;
	levelIntLast = 0;
	PumpReset();
	delayInit(&delayAlarm, ALARM_DELAY_DURATION);
	delayInit(&delayAlarmMin, ALARM_UART_MIN_DELAY_DURATION);
	delayInit(&delayAlarmMax, ALARM_UART_MAX_DELAY_DURATION);

}

void FSMStateNew(FSMState_t stateNew) {

	stateLast = stateCurrent;
	stateCurrent = stateNew;

}

void FSMStateRevert(void) {

	stateCurrent = stateLast;

}

bool FSMIsNumber(char keyIsNumber) {

	if (keyIsNumber >= '0' && keyIsNumber <= '9') {

		return true;

	}

	return false;

}

void FromStringToInt(char *charVectorArg, uint16_t *intArg) {

	sscanf(charVectorArg, "%hd", intArg);
	for (uint8_t i = 0; i < DOSAGE_CANT_CHAR; i++)
		charVectorArg[i] = '\0';

}

void FSMUpdate(void) {

	key = KeypadDebounceFSMUpdate();

	switch (stateCurrent) {
	case IDLE:

		if (key == empty)
			ScreenMainInfUpdate();

		if (key == dosage) {
			FSMStateNew(DOSAGE_1);

			LCDPosition(0, 1);
			LCDSendString((uint8_t*) "DOSIS:      mL/min  ");
			LCDPosition(7, 1);
			LCDBlinkOn();
			break;

		}

		if (key == pump) {
			FSMStateNew(PUMP);
			break;
		}

		break;

	case DOSAGE_1:

		if (FSMIsNumber(key)) {
			dosageCharVector[0] = key;
			LCDSendData(key);
			FSMStateNew(DOSAGE_2);
			break;
		}

		if (key == back) {
			FSMStateNew(BACK);
			break;
		}

		if (key == pump) {
			FSMStateNew(PUMP);
			break;
		}

		ScreenDosageInfUpdate(DOSAGE_1);

		break;

	case DOSAGE_2:

		if (FSMIsNumber(key)) {
			dosageCharVector[1] = key;
			LCDSendData(key);
			FSMStateNew(DOSAGE_3);
			break;
		}

		if (key == back) {
			FSMStateNew(BACK);
			break;
		}

		if (key == pump) {
			FSMStateNew(PUMP);
			break;
		}

		ScreenDosageInfUpdate(DOSAGE_2);

		break;

	case DOSAGE_3:

		if (FSMIsNumber(key)) {
			dosageCharVector[2] = key;
			LCDSendData(key);
			FSMStateNew(DOSAGE_4);
			break;
		}

		if (key == back) {
			FSMStateNew(BACK);
			break;
		}

		if (key == pump) {
			FSMStateNew(PUMP);
			break;
		}

		ScreenDosageInfUpdate(DOSAGE_3);

		break;

	case DOSAGE_4:

		if (FSMIsNumber(key)) {
			dosageCharVector[3] = key;
			FromStringToInt(dosageCharVector, &dosageAux);

			if (dosageAux >= DOSAGE_MIN_VALUE
					&& dosageAux <= DOSAGE_MAX_VALUE) {

				LCDBlinkOff();
				ScreenDosageAsk();

				LCDPosition(7, 1);
				sprintf(dosageScreenString, "%4d", dosageAux);
				LCDSendString((uint8_t*) dosageScreenString);

				FSMStateNew(DOSAGE_ASK);
				break;

			} else {

				ScreenDosageError();
				FSMStateNew(DOSAGE_1);
				break;
			}
		}

		if (key == back) {
			FSMStateNew(BACK);
			break;
		}

		if (key == pump) {
			FSMStateNew(PUMP);
			break;
		}

		if (key == ok) {
			FSMStateNew(DOSAGE_VERIF);
			break;
		}

		ScreenDosageInfUpdate(DOSAGE_4);

		break;

	case DOSAGE_ASK:

		if (key == ok) {
			dosageInt = dosageAux;
			dosageAux = 0;
			ScreenMain();
			FSMStateNew(IDLE);

		}

		if (key == back) {
			dosageAux = 0;
			ScreenMain();
			FSMStateNew(IDLE);

		}

		if (key == pump) {
			FSMStateNew(PUMP);
			break;
		}

		break;

	case DOSAGE_VERIF:

		FromStringToInt(dosageCharVector, &dosageAux);

		if (dosageAux >= DOSAGE_MIN_VALUE && dosageAux <= DOSAGE_MAX_VALUE) {

			LCDBlinkOff();
			ScreenDosageAsk();

			LCDPosition(7, 1);
			sprintf(dosageScreenString, "%4d", dosageAux);
			LCDSendString((uint8_t*) dosageScreenString);

			FSMStateNew(DOSAGE_ASK);
			break;

		} else {

			ScreenDosageError();
			FSMStateNew(DOSAGE_1);
			break;
		}

		break;

	case BACK:

		ScreenMain();
		FSMStateNew(IDLE);

		break;

	case PUMP:

		if (pumpFlagAlarm == 0) {

			if (pumpState == true) {
				pumpState = false;
				PumpReset();

			} else {
				pumpState = true;
				PumpSet();

			}

		} else {
			pumpState = 0;
			PumpReset();
		}
		FSMStateRevert();//Ejecutamos FSMStateRevert() porque debemos volver al estado anterior ya que luego de cambiar el estado de la bomba, debemos continuar con la ejecucion normal en la que estabamos anteriormente.

		break;

	default:
		FSMInit();

		break;
	}

}

void AlarmUpdate(void) {

	if (LevelSensorGetAlarmLevel(ALARM_ACTIVATION_MAX_THRESHOLD) == ALARM_ON) {

		if (LevelSensorGetAlarmLevel(ALARM_ACTIVATION_MIN_THRESHOLD)
				== ALARM_ON) {

			LevelSensorSetAlarm();

			if (delayRead(&delayAlarmMin)) {

				UARTSendString(
						(uint8_t*) "WARNING: ALARM_MIN_TH ACTIVATED - EXTREMELY LOW LIQUID LEVEL - PUMP OFF\n");
			}

			pumpState = 0;
			PumpReset();
			pumpFlagAlarm = 1;

		} else {

			if (delayRead(&delayAlarm)) {

				LevelSensorToggleAlarm();

			}

			if (delayRead(&delayAlarmMax)) {
				UARTSendString(
						(uint8_t*) "WARNING: ALARM_MAX_TH ACTIVATED - LOW LIQUID LEVEL\n");
			}
		}

	} else {

		LevelSensorResetAlarm();
		pumpFlagAlarm = 0;
		delayInit(&delayAlarmMin, ALARM_UART_MIN_DELAY_DURATION);
		delayInit(&delayAlarmMax, ALARM_UART_MAX_DELAY_DURATION);
	}

}
