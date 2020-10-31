#pragma once
#include <stdint.h>

void SysTick_init();

void SysTick_Handler       ( void );

//uint32_t time_running_ms();

uint32_t return_milliseconds();