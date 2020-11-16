#pragma once
#include <stdint.h>
#include "joystick_driver.h"
//#include "protagonists.h"
#include <util/delay.h>

typedef struct
{
	char* labels[8];

	struct menu* links[8];

	void (*f[8]) (void);

	uint8_t selected;
	
} menu;

menu* new_menu(menu* parent);

void write_menu_to_screen(menu* menuPointer);

void change_menu(menu* next_menu, menu** menuHead);

void invert_selected(menu* menuPointer);

void change_selected(menu** menuHead, DIRECTION d);

void button_pressed(menu** menuHead);

void launch_menusystem();

void wojakprinter();

void hello_world();

void choose_character();

void play_game();

void calibrate();

void set_easy();

void set_medium();

void set_hard();

void show_credits();

void hiscore();

void reset_scores();

void reaction_test();