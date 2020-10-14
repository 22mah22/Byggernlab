#include "menu.h"
#include "OLED_driver.h"
#include <string.h>
#include "protagonists.h"
#include "joystick_driver.h"

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
		mymenu->f[i] = NULL;
		mymenu->labels[i] = string_list[i];
	}
	
	(mymenu->selected) = 0;
	mymenu->links[7] = parent;
	mymenu->labels[7] = "<- Back";
	mymenu->fun_ptr = NULL;
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

//Husk: Funksjoner i C kan bare endre minneomr�det til pekerene som sendes inn.
//Dvs at denne setter minneomr�det prev peker p� til minneomr�det next peker p�.
//Har dette �nsket hensikt? Kan det l�ses med � ha en overordnet peker-til-peker?
void change_menu(menu* next_menu, menu** menuHead){
	/*if (next_menu->fun_ptr != NULL){
		(*(next_menu->fun_ptr));
	}*/

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
		while(((*(menuHead))->labels[((*(menuHead))->selected)]) == ""){
			((*(menuHead))->selected)--;
		}
		printf("%d up",((*(menuHead))->selected));
	}
	if(d == DOWN){
		((*(menuHead))->selected)++;
		while(((*(menuHead))->labels[((*(menuHead))->selected)]) == ""){
			((*(menuHead))->selected)++;
		}
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
	if((*(menuHead))->f[((*(menuHead))->selected)] != NULL){
		(*f[((*(menuHead))->selected)])(void);
		write_menu_to_screen(*(menuHead));
	}
	else if((*(menuHead))->links[((*(menuHead))->selected)] != NULL){
		change_menu((*(menuHead))->links[((*(menuHead))->selected)], menuHead);
	}
}

void launch_menusystem(){
	//SETUP
	menu** headPointer = NULL;
	
	menu* mainMenu;
	mainMenu = new_menu(NULL);
	menu* submenu = new_menu(mainMenu);
	menu* submenu_4 = new_menu(mainMenu);
	menu* submenu_5 = new_menu(mainMenu);
	
	mainMenu->labels[0] = "submenu_demo";
	mainMenu->labels[1] = "do_nothing";
	mainMenu->labels[2] = "";
	mainMenu->labels[3] = "empty_submenu";
	mainMenu->labels[4] = "empty_submenu";
	mainMenu->labels[5] = "";
	mainMenu->labels[6] = "";
	mainMenu->labels[7] = "";
	mainMenu->links[0] = submenu;
	mainMenu->links[3] = submenu_4;
	mainMenu->links[4] = submenu_5;
	
	submenu->labels[0] = "do_nothing";
	submenu->labels[1] = "laks";
	submenu->labels[2] = "salami";
	submenu->labels[3] = "draw a wojak";
	submenu->f[3] = wojakprinter;
	submenu->labels[4] = "";
	submenu->labels[5] = "";
	submenu->labels[6] = "";
	
	
	//INITIATE
	write_menu_to_screen(mainMenu);
	headPointer = &mainMenu;
	const int *BASE = 0x1000;
	volatile amap* atmelMap = (amap*) BASE;
	
	//RUN
	while(1){
		uint8_t val = 1;
		atmelMap->ADC[1] = 0x04;
		uint8_t valx = atmelMap->ADC[1];
		uint8_t valy = atmelMap->ADC[1];
		uint8_t vall = atmelMap->ADC[1];
		uint8_t valr = atmelMap->ADC[1];
		
		uint8_t left_button = PIND & (1<< PIND4);
		uint8_t right_button = PIND & (1<< PIND5);
		uint8_t joy_button = PINB & (1<< PINB1);
		
		calc_pos(&joystick,valx,valy);
		calc_pos_slider(&slider,vall,valr);
	
		_delay_ms(1);
		DIRECTION current_dir = joystick_direction(current_dir, joystick);
		if(current_dir != NEUTRAL && current_dir != WAITING){
			change_selected(headPointer, current_dir);
		}
		if(button_check(joy_button)){
			button_pressed(headPointer);
		}
	}
}

void wojakprinter(){
	clear_oled();
	character_printer(wojak, 64, 40);
	while((PINB & (1<< PINB1))){}
	return;
}