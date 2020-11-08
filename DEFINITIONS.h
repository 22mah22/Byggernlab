#pragma once
#include <stdint.h>

#define F_CPU 4915200
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1


//const int *BASE = 0x1000;
typedef struct {
	uint8_t OLED_CMD[512];
	uint8_t OLED_DATA[512];
	uint8_t ADC[1024];
	uint8_t SRAM[2048];
} amap;

#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))