#pragma once
#include <stdint.h>

void TC1_Handler       ( void );

uint8_t get_difficulty();

void set_difficulty(uint8_t difficulty_to_set);