/**
 * @file
 * @brief A module for handling a timer using systick.
 */

#pragma once
#include <stdint.h>

void SysTick_init();

void SysTick_Handler       ( void );

//uint32_t time_running_ms();

uint32_t return_milliseconds();

uint16_t return_seconds();

uint16_t return_starttime();

void set_starttime();