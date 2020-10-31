#pragma once
#include <stdint.h>
#include "DEFINITIONS.h"
#include "can_driver.h"


typedef struct {
	int8_t x_val;
	int8_t y_val;
} joyVal;

typedef struct {
	uint8_t l_val;
	uint8_t r_val;
} sliderVal;

typedef enum{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		NEUTRAL,
		WAITING
} DIRECTION;

void get_adc_data(amap* atmelMap, joyVal* stick, sliderVal* slider);

void calc_offset();

void calc_pos_stick(joyVal* values, char* adc);

void calc_pos_slider(sliderVal* values, uint8_t left, uint8_t right);

uint8_t button_check(uint8_t current);

void update_adc_values(joyVal* stick, sliderVal* slider);

void send_stick_can(joyVal joystick, sliderVal slider);


//DIRECTION joystick_direction(joyVal stick);

DIRECTION joystick_direction(DIRECTION dir, joyVal stick);

DIRECTION calc_dir(joyVal* val);