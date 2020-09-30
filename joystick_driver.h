#pragma once
#include <stdint.h>
#include "DEFINITIONS.h"


typedef struct {
	int8_t x_val;
	int8_t y_val;
} joyVal;

typedef struct {
	uint8_t l_val;
	uint8_t r_val;
} sliderVal;

static joyVal joystick;
static sliderVal slider;

void get_adc_data(amap* atmelMap, joyVal* stick, sliderVal* slider);

void calc_offset(amap* atmelMap);

void calc_pos_stick(joyVal* values, uint8_t x, uint8_t y);

void calc_pos_slider(sliderVal* values, uint8_t left, uint8_t right);

uint8_t button_check(uint8_t current);



typedef enum{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		NEUTRAL,
		WAITING
} DIRECTION;

//DIRECTION joystick_direction(joyVal stick);

DIRECTION joystick_direction(DIRECTION dir, joyVal stick);

DIRECTION calc_dir(joyVal* val);