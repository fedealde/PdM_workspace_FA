/*
 * API_LCD.h
 *
 *  Created on: Apr 4, 2024
 *      Author: flealu
 */



#ifndef API_INC_API_LCD_H_
#define API_INC_API_LCD_H_

#include <stdint.h>
#include <stdbool.h>


//Defined by RS, but we separate into 2 macros
#define LCD_CONTROL 0
#define LCD_DATA 1

//Defines for bits/signals
#define LCD_RW (1<<1)	//R/W 1/0
#define LCD_EN (1<<2)	//Enable
#define LCD_BL (1<<3)	//Backlight

//Commands to initialize LCD
#define LCD_INI_CMD_1 0x30
#define LCD_INI_CMD_2 0x20

//Delays for LCD
#define LCD_SEND_DELAY_20MS 20
#define LCD_SEND_DELAY_2MS  2
#define LCD_SEND_DELAY_1MS  1

//These defines come from the command table (jhonson code)
#define LCD_CLEAR 1
#define LCD_RETURN_HOME (1<<1)
#define LCD_ENTRY_MODE (1<<2)
#define LCD_DISPLAY_CONTROL (1<<3)
#define LCD_CURSOR_DISPLAY_SHIFT (1<<4)
#define LCD_FUNTION_SET (1<<5)
#define LCD_SET_CGRAM (1<<6)
#define LCD_SET_DDRAM (1<<7)

//These are commands to be sent
#define LCD_DISPLAY_ON (1<<2)
#define LCD_CURSOR_ON (1<<1)
#define LCD_CURSOR_BLINK 1
#define LCD_AUTO_INCREMENT (1<<1)
#define LCD_4BIT_MODE 0x28

//Nibbles
#define HIGH_NIBBLE 0xf0
#define LOW_NIBBLE_TO_HIGH 0x04

/**
 * @brief It Initializes and sets LCD
 *
 * @return true if ok, or false in case of error
 */
bool LCDInit(void);

// ///////////////////////////////////////
/**
 * @brief It sends a string to the LCD until /0
 *
 * @param text as a string
 */
void LCDSendString (uint8_t *text);

/**
 * @brief It send general data to LCD
 *
 * @param data just a character
 */
void LCDSendData (uint8_t data);

/**
 * @brief It sends data but with offset as ASCII data (+'0') to LCD
 *
 * @param ASCIIdata just a character
 */
void LCDSendASCII (uint8_t ASCIIdata);

/**
 * @brief It sends BDC data to LCD - Its like sending the binary as a nibble
 *
 * @param BDCdata just a character
 */
void LCDSendBDC (uint8_t BDCdata); //To represent 12 its 0001 0010 BDC, so we send 18 INT
// ///////////////////////////////////////

// ///////////////////////////////////////
/**
 * @brief It clears LCD
 *
 */
void LCDClear(void);

/**
 * @brief It positions the cursor at zero point position
 *
 */
void LCDHome(void);
// ///////////////////////////////////////

// ///////////////////////////////////////
/**
 * @brief It turns on the display
 *
 */
void LCDDisplayOn(void);

/**
 * @brief It turns off the display
 *
 */
void LCDDisplayOff(void);
// ///////////////////////////////////////


/**
 * @brief It positions the cursor at "position" in "row"
 *
 * @param positon
 * @param row
 */
void LCDPosition(uint8_t positon, uint8_t row);


// ///////////////////////////////////////
/**
 * @brief It turns off the cursor
 *
 */
void LCDCursorOff(void);
/**
 * @brief It turns on the cursor
 *
 */
void LCDCursorOn(void);

// ///////////////////////////////////////
/**
 * @brief It turns off the blinking character
 *
 */
void LCDBlinkOff(void);

/**
 * @brief It turns of the blinking character
 *
 */
void LCDBlinkOn(void);




















#endif /* API_INC_API_LCD_H_ */
