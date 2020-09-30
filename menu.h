#pragma once
#include <stdint.h>
#include "joystick_driver.h"
#include <util/delay.h>

typedef struct
{
	char* labels[8];

	struct menu* links[8];

	uint8_t selected;
} menu;

menu* new_menu(menu* parent);

void write_menu_to_screen(menu* menuPointer);

void change_menu(menu* next_menu, menu** menuHead);

void invert_selected(menu* menuPointer);

void change_selected(menu** menuHead, DIRECTION d);

void button_pressed(menu** menuHead);