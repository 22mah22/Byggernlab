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
	int8_t left_val;
	int8_t right_val;
} joyVal;

extern uint8_t y_value_pi; // value for use in pi controller

joyVal joystick;

void move_solenoid();


void change_motor_speed();

void motor_box_init();

uint8_t encoder_read();

uint8_t button_check(uint8_t current);