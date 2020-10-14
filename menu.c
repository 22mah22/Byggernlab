#include "menu.h"
#include "OLED_driver.h"
#include <string.h>
#include "protagonists.h"
#include "joystick_driver.h"
#include "menuconfigs.h"

char* string_list[] = {
	"Option 1",
	"Option 2",
	"Option 3",
	"Option 4",
	"Option 5",
	"Option 6",
	"Option 7",
	"<- Back"
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
		(*(menuHead))->f[((*(menuHead))->selected)]();
		write_menu_to_screen(*(menuHead));
	}
	else if((*(menuHead))->links[((*(menuHead))->selected)] != NULL){
		change_menu((*(menuHead))->links[((*(menuHead))->selected)], menuHead);
	}
}

void launch_menusystem(){
	
	//INITIATE
	menu** headPointer = NULL;
	
		static menu* mainMenu;
		mainMenu = new_menu(NULL);
		menu* submenu = new_menu(mainMenu);
		menu* submenu_5 = new_menu(mainMenu);
		
		mainMenu->labels[0] = "Demo of a submenu";
		mainMenu->labels[1] = "Choose character";
		mainMenu->f[1] = choose_character;
		mainMenu->labels[2] = "";
		mainMenu->labels[3] = "Write greeting";
		mainMenu->f[3] = hello_world;
		mainMenu->labels[4] = "Default submenu";
		mainMenu->labels[5] = "";
		mainMenu->labels[6] = "";
		mainMenu->labels[7] = "";
		mainMenu->links[0] = submenu;
		mainMenu->links[4] = submenu_5;
		
		submenu->labels[0] = "Do nothing";
		submenu->labels[1] = "Loaf around";
		submenu->labels[2] = "funny women";
		submenu->labels[3] = "Draw a wojak";
		submenu->f[3] = wojakprinter;
		submenu->labels[4] = "";
		submenu->labels[5] = "";
		submenu->labels[6] = "";
		
		
	headPointer = &mainMenu;
	write_menu_to_screen(*headPointer);
	const int *BASE = 0x1000;
	const int *ADC = 0x1401;
	volatile amap* atmelMap = (amap*) BASE;
	 
	calc_offset();

	//RUN
	while(1){
		
		update_adc_values(&joystick, &slider);
		
		uint8_t left_button = PIND & (1<< PIND4);
		uint8_t right_button = PIND & (1<< PIND5);
		uint8_t joy_button = PINB & (1<< PINB1);
	
		printf("\r J_x: %4d, J_y: %4d, J_b: %3d Slider 1: %3d, Slider 2: %3d |||| %3d,%3d",joystick.x_val,joystick.y_val,joy_button<1,slider.l_val,slider.r_val,left_button>1,right_button>1);
	
		//_delay_ms(1);
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
	
	_delay_ms(1000);
	while((PINB & (1<< PINB1))){}
	return;
}

void hello_world(){
	clear_oled();
	oled_write_string(0, "Hello world!", 8);
	oled_write_string(7, "Joystick-return", 8);
	_delay_ms(1000);
	while((PINB & (1<< PINB1))){}
	return;
}

void choose_character(){
	clear_oled();
	oled_write_string(0, "CHOOSE!", 8);

	//INVERT LEFT PICTURE
	for (int line = 1; line < 9; line++){
			int offset = line*5*8;
			for (int col = 0; col < 5; col++){
				char c = 0b00000000;
				for (int i = 0; i < 8; i++){
					c |= (pgm_read_byte(&(wojak[i*5 + col + offset])) << i);
				}
				go_to_line(line);
				go_to_column(col/*+p*/);
				oled_write_data(~c);
			}
		}
	for (int line = 1; line < 9; line++){
			int offset = line*5*8;
			for (int col = 0; col < 5; col++){
				char c = 0b00000000;
				for (int i = 0; i < 8; i++){
					c |= (pgm_read_byte(&(pepe[i*5 + col + offset])) << i);
				}
				go_to_line(line);
				go_to_column(col/*+p*/);
				oled_write_data(c);
			}
		}
	
	while(1){
		update_adc_values(&joystick, &slider);
		
		uint8_t left_button = PIND & (1<< PIND4);
		uint8_t right_button = PIND & (1<< PIND5);
		uint8_t joy_button = PINB & (1<< PINB1);
	
		DIRECTION current_dir = joystick_direction(current_dir, joystick);
		if(current_dir != NEUTRAL && current_dir != WAITING){
			if (current_dir == RIGHT){
				//INVERT RIGHT PICTURE
				clear_oled();
				oled_write_string(0, "CHOOSE!", 8);

				for (int line = 1; line < 9; line++){
					int offset = line*5*8;
					for (int col = 0; col < 5; col++){
						char c = 0b00000000;
						for (int i = 0; i < 8; i++){
							c |= (pgm_read_byte(&(wojak[i*5 + col + offset])) << i);
						}
						go_to_line(line);
						go_to_column(col/*+p*/);
						oled_write_data(c);
					}
				}
				for (int line = 1; line < 9; line++){
						int offset = line*5*8;
					for (int col = 0; col < 5; col++){
						char c = 0b00000000;
						for (int i = 0; i < 8; i++){
							c |= (pgm_read_byte(&(pepe[i*5 + col + offset])) << i);
						}
						go_to_line(line);
						go_to_column(col/*+p*/);
						oled_write_data(~c);
					}
				}
			}
			//INVERT LEFT PICTURE
			else if (current_dir == LEFT){
				clear_oled();
				oled_write_string(0, "CHOOSE!", 8);

				for (int line = 1; line < 9; line++){
					int offset = line*5*8;
					for (int col = 0; col < 5; col++){
						char c = 0b00000000;
						for (int i = 0; i < 8; i++){
							c |= (pgm_read_byte(&(wojak[i*5 + col + offset])) << i);
						}
						go_to_line(line);
						go_to_column(col/*+p*/);
						oled_write_data(~c);
					}
				}
				for (int line = 1; line < 9; line++){
						int offset = line*5*8;
					for (int col = 0; col < 5; col++){
						char c = 0b00000000;
						for (int i = 0; i < 8; i++){
							c |= (pgm_read_byte(&(pepe[i*5 + col + offset])) << i);
						}
						go_to_line(line);
						go_to_column(col/*+p*/);
						oled_write_data(c);
					}
				}
			}
		}
		if(button_check(joy_button)){
			return;
		}
	}
}