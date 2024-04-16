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
