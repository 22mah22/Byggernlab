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
	mymenu->labels[7] = "<- Back";
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

//Husk: Funksjoner i C kan bare endre minneområdet til pekerene som sendes inn.
//Dvs at denne setter minneområdet prev peker på til minneområdet next peker på.
//Har dette ønsket hensikt? Kan det løses med å ha en overordnet peker-til-peker?
void change_menu(menu* next_menu, menu** menuHead){
	write_menu_to_screen(next_menu);
	*menuHead = next_menu;
}

void invert_selected(menu* menuPointer){
	go_to_column(0);
	oled_write_string_inverted((menuPointer->selected), menuPointer->labels[(menuPointer->selected)], 8);
}

void change_selected(menu** menuHead, DIRECTION d){
	if(d == UP){
		((*(menuHead))->selected)--;
		printf("%d up",((*(menuHead))->selected));
	}
	if(d == DOWN){
		((*(menuHead))->selected)++;
		printf("%d down",((*(menuHead))->selected));
	}
	if(((*(menuHead))->selected) == 8){
		((*(menuHead))->selected) = 0;
	}
	if(((*(menuHead))->selected) == 255){
		((*(menuHead))->selected) = 7;
	}
	if(d != WAITING && d != NEUTRAL){
		write_menu_to_screen(*(menuHead));
	}
	
}

void button_pressed(menu** menuHead){
	if((*(menuHead))->links[((*(menuHead))->selected)] != NULL){
		change_menu((*(menuHead))->links[((*(menuHead))->selected)], menuHead);
	}
}
