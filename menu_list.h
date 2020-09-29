/*
 * menu_list.h
 *
 * Created: 23.09.2020 16:57:57
 *  Author: magneah
 */ 
#pragma once

#include "joystick_driver.h"
/*
uint8_t totalMenuItems;
uint8_t current_line;
uint8_t current_line_max;
uint8_t current_col;
uint8_t current_col_max;
DIRECTION direction;
*/
typedef struct{
	struct menuItem* prev;
	struct menuItem* next;
	struct menuItem* parent;
	struct menuItem* child;
	uint8_t line;
	char* label;
}menuItem;

void insertion_beginning(char *label, uint8_t line); 

void insertion_last(char *label, uint8_t line); 

void child_insertion_last(char *parentlabel, char *label, uint8_t line);

void insertion_specified(char *label, uint8_t line); 

void deletion_beginning(); 

void deletion_last(); 

void deletion_specified(char *label); 

void search();

void update_position(DIRECTION dir);

void button_action();

DIRECTION joystick_check(DIRECTION dir, joyVal stick);

uint8_t write_menu(menuItem *currentHead);

menuItem* menuItem_at_line(menuItem *currentHead, uint8_t linje);

void init_main(char* list[]);

void init_child(char* list[]);

