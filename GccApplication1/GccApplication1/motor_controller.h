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
	int8_t left_button;
	int8_t right_button;
} joyVal;

extern uint8_t y_value_pi; // value for use in pi controller

joyVal joystick;

uint8_t get_solenoid_status();

void reset_solenoid_status();

void move_solenoid();

void check_solenoid_shot();

void change_motor_speed();

void change_motor_speed_using_paadrag(int paadrag);

void motor_box_init();

uint8_t encoder_read();

uint8_t button_check(uint8_t current);