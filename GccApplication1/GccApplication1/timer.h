#pragma once
#include <stdint.h>

void timer_init();

void SysTick_Handler       ( void );

uint16_t time_running_ms();