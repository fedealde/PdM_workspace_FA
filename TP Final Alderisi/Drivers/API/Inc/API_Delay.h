/**
 * @brief API_delay.h
 *
 * @author Author: Federico Alderisi
 * @date Created on: Mar 14, 2024
 *
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

/**
 * @typedef tick_t
 * @brief Used to compare ticks from HAL function
 *
 */
typedef uint32_t tick_t;
/**
 * @typedef bool_t
 * @brief Used as state of timer
 *
 */
typedef bool bool_t;

/**
 * @typedef delay_t
 * @brief Struct used as timer
 * @param startTime take the actual time
 * @param duration is the time to be compare
 * @param running is the state of timer, could be true or false
 *
 */
typedef struct {
	tick_t startTime;
	tick_t duration;
	bool_t running;
} delay_t;

/**
 * @brief initialize the delay struct
 * @param delay: pointer to a delay struct to be initialized
 * @param duration: duration of the timer
 *
 * */

void delayInit(delay_t *delay, tick_t duration);
/**
 * @brief depending on the state, it initialize the timer if it is off
 * or compare with duration if it is running. As the time elapses, it return
 * a bool_t
 *
 * @param delay
 * @return true if elapsed and false otherwise
 */
bool_t delayRead(delay_t *delay);

/**
 * @brief used to write new duration in a timer struct
 *
 * @param delay: pointer to a delay struct to be written
 * @param duration: duration of the timer to be write, running or not
 */
void delayWrite(delay_t *delay, tick_t duration);

/**
 * @brief turn on a led on a while loop
 *
 */

#endif /* API_INC_API_DELAY_H_ */
