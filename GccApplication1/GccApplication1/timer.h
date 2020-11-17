/**
 * @file
 * @brief Driver module for asynchronous timer functionallity
 */

#pragma once
#include <stdint.h>

/**
 * @brief Function to set the systick registers on the atsam.
 * Allows us to generate an interrupt at a set number of clock cycles
 */
void SysTick_init();

/**
 * @brief Function that is called by the systick interrupt
 * is ideally called every millisecond and therefore increments a counter
 */
void SysTick_Handler       ( void );

/**
 * @brief Function to return milliseconds since program start
 * @return milliseconds gone by
 */
uint32_t return_milliseconds();

/**
 * @brief Function to return seconds since program start
 * @return seconds gone by
 */
uint16_t return_seconds();

/**
 * @brief Function to return a starttime defined by a CAN interrupt
 * @return the last set starttime
 */
uint16_t return_starttime();

/**
 * @brief Function to set starttime to the current number of seconds gone by
 */
void set_starttime();