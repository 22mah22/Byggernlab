#include "menu.h"
#include "OLED_driver.h"
#include <string.h>

char* string_list[] = {
	"option1",
	"option2",
	"option3",
	"option4",
	"option5",
	"option6",
	"option7",
	"option8",
};
menu* new_menu(menu* parent){
	menu* mymenu = malloc(sizeof(menu));
	for(unsigned int i = 0; i < 8; i++){
		mymenu->links[i] = NULL;
		mymenu->labels[i] = string_list[i];
	}
	
	(mymenu->selected) = 0;
	mymenu->links[7] = (parent);
	//menu->labels[7] = "<- Back";
	return mymenu;
}

void write_menu_to_screen(menu* menuPointer){
	clear_oled_new();
	for(unsigned int i = 0; i < 8; i++){
		go_to_column(0);
		oled_write_string(i, menuPointer->labels[i], 8);
	}
	invert_selected(menuPointer);
}

void change_menu(menu* next_menu, menu* prev_menu){
	write_menu_to_screen(next_menu);
	*prev_menu = *next_menu;
}

void invert_selected(menu* menuPointer){
	go_to_column(0);
	oled_write_string_inverted((menuPointer->selected), menuPointer->labels[(menuPointer->selected)], 8);
}

void change_selected(menu* menuPointer, DIRECTION d){
	if(d == UP){
		(menuPointer->selected)--;
		printf("%d up",(menuPointer->selected));
	}
	if(d == DOWN){
		(menuPointer->selected)++;
		printf("%d down",(menuPointer->selected));
	}
	if((menuPointer->selected) == 8){
		(menuPointer->selected) = 0;
	}
	if((menuPointer->selected) == 255){
		(menuPointer->selected) = 7;
	}
	if(d != WAITING && d != NEUTRAL){
		write_menu_to_screen(menuPointer);
	}
	
}

void button_pressed(menu* menuPointer){
	if(menuPointer->links[(menuPointer->selected)] != NULL){
		change_menu(menuPointer->links[(menuPointer->selected)], menuPointer);
	}
}
