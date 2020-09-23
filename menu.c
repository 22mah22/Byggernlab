#include "menu.h"
#include "OLED_driver.h"
#include <string.h>


menu* new_menu(menu* parent){
	menu* mymenu = malloc(sizeof(menu));
	for(unsigned int i = 0; i < 8; i++){
		mymenu->links[i] = NULL;
	}
	mymenu->labels = "salat";
	*(mymenu->selected) = 0;
	mymenu->links[7] = &(*parent);
	//menu->labels[7] = "<- Back";
	return mymenu;
}

void write_menu_to_screen(menu* menuPointer){
	clear_oled_new();
	for(unsigned int i = 0; i < 8; i++){
		go_to_column(0);
		oled_write_string(i, menuPointer->labels, 8);
	}
	invert_selected(menuPointer);
}

void change_menu(menu* next_menu, menu* prev_menu){
	write_menu_to_screen(next_menu);
	*prev_menu = *next_menu;
}

void invert_selected(menu* menuPointer){
	go_to_column(0);
	oled_write_string_inverted(*(menuPointer->selected), menuPointer->labels, 8);
}

void change_selected(menu* menuPointer, DIRECTION d){
	if(d == UP){
		*(menuPointer->selected)++;
	}
	if(d == DOWN){
		*(menuPointer->selected)--;
	}
	if(*(menuPointer->selected) == 8){
		*(menuPointer->selected) = 0;
	}
	if(*(menuPointer->selected) == -1){
		*(menuPointer->selected) = 7;
	}
	write_menu_to_screen(menuPointer);
}

void button_pressed(menu* menuPointer){
	if(menuPointer->links[*(menuPointer->selected)] != NULL){
		change_menu(menuPointer->links[*(menuPointer->selected)], menuPointer);
	}
}
