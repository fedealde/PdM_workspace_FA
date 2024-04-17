/*
 * API_FSM.c
 *
 *  Created on: Apr 16, 2024
 *      Author: flealu
 */

#include "API_FSM.h"

uint16_t dosageInt = 300;
uint16_t dosageLast = 300;
uint8_t levelInt = 0;
uint8_t levelIntLast = 0;
uint8_t dosageVector[4] = { 0 };
char dosisString[20] = { 0 };
char levelString[20] = { 0 };
char key = '\0';
char one = '1', two = '2', three = '3', four = '4', five = '5', six = '6',
		seven = '7', eight = '8', nine = '9', zero = '0', up = 'U', down = 'W',
		ok = 'K', back = 'B', dosage = 'D', pump = 'P';
bool pumpState = 0;
bool pumpStateLast = 0;
FSMState_t stateCurrent = IDLE, stateLast = IDLE;

void ScreenMain(void) {

	LCDHome();
	LCDSendString((uint8_t*) "     DOSIFICADOR");

	LCDPosition(0, 1);
	LCDSendString((uint8_t*) "DOSIS:      mL/min");
	ScreenUpdateDosage();

	LCDPosition(0, 2);
	ScreenUpdatePump();

	LCDPosition(0, 3);
	LCDSendString((uint8_t*) "NIVEL:    %");
	ScreenUpdateLevel();

}

void ScreenTemplate(void) {

	LCDHome();
	LCDSendString((uint8_t*) "     DOSIFICADOR");

	LCDPosition(0, 1);
	LCDSendString((uint8_t*) "DOSIS:      mL/min");

	LCDPosition(0, 2);
	LCDSendString((uint8_t*) "BOMBA:    ");

	LCDPosition(0, 3);
	LCDSendString((uint8_t*) "NIVEL:    %");


}

void ScreenUpdateDosage(void) {

	LCDPosition(7, 1);
	sprintf(dosisString, "%4d", dosageInt);
	LCDSendString((uint8_t*) dosisString);
}

void ScreenUpdatePump(void) {

	LCDPosition(0, 2);
	if (pumpState) {
		LCDSendString((uint8_t*) "BOMBA: ON ");

	} else {
		LCDSendString((uint8_t*) "BOMBA: OFF");
	}
}

void ScreenUpdateLevel(void) {

	LCDPosition(7, 3);
	LevelSensorGetCurrentLevel(&levelInt);
	sprintf(levelString, "%3d", levelInt);
	LCDSendString((uint8_t*) levelString);

}

void ScreenDosageAsk(void) {

	LCDClear();
	LCDHome();
	LCDSendString((uint8_t*) "     DOSIFICADOR");
	LCDPosition(0, 1);
	LCDSendString((uint8_t*) "DOSIS:      mL/min");
	LCDPosition(0, 2);
	LCDSendString((uint8_t*) "CONFIRMAR DOSIS?");

}

void ScreenDosageError(void) {

	LCDClear();
	LCDHome();
	LCDSendString((uint8_t*) "     DOSIFICADOR");
	LCDPosition(0, 1);
	LCDSendString((uint8_t*) "DOSIS:      mL/min");
	LCDPosition(0, 2);
	LCDSendString((uint8_t*) "ERROR: INGRESE DOSIS");
	LCDPosition(0, 3);
	LCDSendString((uint8_t*) "   >=300 Y <=3000   ");

}

void FSMInit(void) {

	stateCurrent = IDLE;

}

void FSMStateNew (FSMState_t stateNew){

	stateLast = stateCurrent;
	stateCurrent = stateNew;

}

void FSMStateRevert (void){

	stateCurrent = stateLast;

}

void ScreenMainInfUpdate(void){

	LevelSensorGetCurrentLevel(&levelInt);

	if(dosageInt != dosageLast){ScreenUpdateDosage(); dosageLast = dosageInt;}
	if(levelInt != levelIntLast){ScreenUpdateLevel(); levelIntLast = levelInt;}
	if(pumpState != pumpStateLast){ScreenUpdatePump(); pumpStateLast = pumpState;}

}

void FSMUpdate(void) {

	key = KeypadDebounceFSMUpdate();

	switch (stateCurrent) {
	case IDLE:

		if(key == '\0')ScreenMainInfUpdate();

		if(key == dosage){
			FSMStateNew(DOSAGE_1);

			LCDPosition(0, 1);
			LCDSendString((uint8_t*) "DOSIS:      mL/min");
		}

		if(key == pump){
			FSMStateNew(PUMP);
		}

		break;

	case DOSAGE_1:

		break;

	case DOSAGE_2:

		break;

	case DOSAGE_3:

		break;

	case DOSAGE_4:

		break;

	case DOSAGE_ASK:

		break;

	case DOSAGE_VERIF:

		break;

	case OK:

		break;

	case PUMP:

		pumpState = (!pumpState);
		FSMStateRevert();

		break;

	default:

		break;
	}

}






