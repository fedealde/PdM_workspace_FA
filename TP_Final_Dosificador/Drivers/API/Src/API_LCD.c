/*
 * API_LCD.c
 *
 *  Created on: Apr 4, 2024
 *      Author: flealu
 */

/*4-bit mode is used, because the LCD control need 11 bits to be transfered,
 * 8 for DB0-DB7, Enable, R/W and Register Selector (RS). Therefore we use 4 MSbits
 * DB7-DB4 and E, R/W and RS to send first, then 4LSbits and E, R/W and RS to send second*/

/*All LCD data pins are connected to the PCF8574 where: RS, RW, E, D4, D5, D6 and D7
 * are connected to P0, P1, P2, P4, P5, P6 and P7 respectively.
 * RS is LSB, then RW bit 1, RW bit 2. P3 is connected to the Backlight, therefore is
 * always on */

/* An example to send could be the value (MSB)11001010(LSB) but to send this data, it is needed
 * to separate in 2 parts, 1100 and 1010 to be sent, first it the part where MSB was and then
 * the part where LSB was. Each time a byte is sent, EN should be on, a delay is executed, then off
 * and a delay is executed again, therefore the data is saved between the delay time.
 * The information finally is sent as follow 1 1 0 1 BL EN R/W RS (BL 1 EN 1 R/W 0 (writing) RS 1 data)
 * 1101 1101 and execute a delay; we maintain the value and change EN to 0, (1101 1001) with a delay.
 * This is just for for the half byte of data.
 *
 * Then we send 1 0 1 0 BL EN R/W RS -> 1010 1101, it is executed a delay and then maintain the data
 * but with EN 0 and a delay is executed again.
 *
 * To send a complete data byte, the function executes 2 times the half data sent
 *
 * */

//Includes just to be used in this .c, therefore the main don't have access to LCD_port and I2C directly
#include "API_LCD.h"
#include "API_LCD_port.h"


#define LCD_ROW_1 0x80
#define LCD_ROW_2 0xC0
#define LCD_ROW_3 0x94
#define LCD_ROW_4 0xD4

static void LCDSendControl (uint8_t controlData);
static void LCDSendNibble (uint8_t nibbleToSend, bool type);
static void LCDSendByte (uint8_t byteToSend, bool type);


static const uint8_t LCDSettingCommands [] = {LCD_4BIT_MODE, LCD_DISPLAY_CONTROL, LCD_RETURN_HOME,
		(LCD_ENTRY_MODE + LCD_AUTO_INCREMENT), (LCD_DISPLAY_CONTROL + LCD_DISPLAY_ON), LCD_CLEAR};

static const uint8_t LCDInitCommands [] = {LCD_INI_CMD_1, LCD_INI_CMD_1, LCD_INI_CMD_1, LCD_INI_CMD_2};

static const uint32_t LCDInitDelays [] = {LCD_SEND_DELAY_20MS, LCD_SEND_DELAY_10MS, LCD_SEND_DELAY_1MS, LCD_SEND_DELAY_10MS};




static void LCDSendNibble (uint8_t nibbleToSend, bool type){

	LCDPortSendByte(nibbleToSend+type+LCD_EN+LCD_BL);
	LCDPortDelay(LCD_SEND_DELAY_1MS);
	LCDPortSendByte(nibbleToSend+type+LCD_BL);
	LCDPortDelay(LCD_SEND_DELAY_1MS);
}



static void LCDSendByte (uint8_t byteToSend, bool type){

	LCDSendNibble(byteToSend&HIGH_NIBBLE, type);
	LCDSendNibble(byteToSend&LOW_NIBBLE_TO_HIGH, type);

}



bool LCDInit(void){

	if(LCDPortInit() =! true) {LCDPortErrorHandler();}

	for(uint8_t i = 0; i < sizeof(LCDInitCommands); i++){

		LCDPortDelay(LCDInitDelays[i]);
		LCDSendNibble(LCDSendLCDInitCommands[i], LCD_CONTROL);

	}

	LCDPortDelay(LCD_SEND_DELAY_2MS);

	for (uint8_t i = 0; i < sizeof(LCDSettingCommands); i++) {

		LCDSendControl(LCDSettingCommands[i]);
		LCDPortDelay(LCD_SEND_DELAY_2MS);

	}

	return true;

}



static void LCDSendControl (uint8_t controlData){

	LCDSendByte(controlData, LCD_CONTROL);

}


void LCDSendString (uint8_t *text){
	while(*text)LCDSendData(*text++);
}

void LCDSendData (uint8_t data){
	LCDSendByte(data, LCD_DATA);
}

void LCDSendASCII (uint8_t ASCIIdata){
	LCDSendByte(data+'0', LCD_DATA);
}

void LCDSendBDC (uint8_t BDCdata){
	LCDSendASCII((BDCdata&0xf0) >> 4);
	LCDSendASCII(BDCdata&0x0f);
}

void LCDClear(void){
	LCDSendControl(LCD_CLEAR);
	LCDPortDelay(LCD_SEND_DELAY_2MS);
}

void LCDClear(void){
	LCDSendControl(LCD_RETURN_HOME);
}

void LCDDisplaytOn(void){
	LCDSendControl(LCD_DISPLAY_CONTROL+LCD_DISPLAY_ON);
}

void LCDDisplayOff(void){
	LCDSendControl(LCD_DISPLAY_CONTROL);
}

void LCDPosition(uint8_t position, uint8_t row){
	LCDSendControl(row | position);
}

void LCDCursorOff(void){
	LCDSendControl(LCD_DISPLAY_CONTROL+LCD_DISPLAY_ON);
}

void LCDCursorOn(void){
	LCDSendControl(LCD_DISPLAY_CONTROL+LCD_DISPLAY_ON+LCD_CURSOR_ON);
}

void LCDBlinkOff(void){
	LCDSendControl(LCD_DISPLAY_CONTROL+LCD_DISPLAY_ON);
}

void LCDBlinkOn(void){
	LCDSendControl(LCD_DISPLAY_CONTROL+LCD_DISPLAY_ON+LCD_CURSOR_ON+LCD_CURSOR_BLINK);
}



//Podría implementarse una función distinta a la principal de enviar quitando BL para controlarlo independientemente








