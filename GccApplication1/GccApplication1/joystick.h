/*
 * joystick.h
 *
 * Created: 14.10.2020 14:47:53
 *  Author: magneah
 */ 

#pragma once

#include <stdint.h>


typedef struct {
	int8_t x_val;
	int8_t y_val;
	int8_t butt_pressed;
} joyVal;

static joyVal joystick;