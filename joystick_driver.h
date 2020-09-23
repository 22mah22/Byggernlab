#pragma once
#include <stdint.h>
#include "DEFINITIONS.h"

uint8_t x_offset = 156;
uint8_t y_offset = 164;

typedef struct {
	int8_t x_val;
	int8_t y_val;
} joyVal;

typedef struct {
	uint8_t l_val;
	uint8_t r_val;
} sliderVal;

void get_adc_data(amap* atmelMap, joyVal* stick, sliderVal* slider);

void calc_offset(amap* atmelMap);

void calc_pos_stick(joyVal* values, uint8_t x, uint8_t y);

void calc_pos_slider(sliderVal* values, uint8_t left, uint8_t right);

typedef enum{
		LEFT,
		UPLEFT,
		RIGHT,
		UPRIGHT,
		UP,
		DOWN,
		NEUTRAL,
} DIRECTION;

DIRECTION calc_dir(joyVal* val);