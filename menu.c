#include "menu.h"
#include "OLED_driver.h"
#include <string.h>
#include "protagonists.h"
#include "joystick_driver.h"
#include "menuconfigs.h"
#include "can_driver.h"

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
	oled_init();
	clear_oled();
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
		mainMenu->labels[5] = "Play ping-pong";
		mainMenu->f[5] = play_game;
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
	character_printer(wojak, 64, 40, 40, 2, 0);
	
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
	character_printer(wojak, 64, 40, 0, 1, 1);
	character_printer(pepe, 64, 40, 64, 1, 0);
	
	uint8_t chosen = 0;
	
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
				character_printer(wojak, 64, 40, 0, 1, 0);
				character_printer(pepe, 64, 40, 64, 1, 1);
				
				chosen = 1;
			}
			//INVERT LEFT PICTURE
			else if (current_dir == LEFT){
				clear_oled();
				oled_write_string(0, "CHOOSE!", 8);
				character_printer(wojak, 64, 40, 0, 1, 1);
				character_printer(pepe, 64, 40, 64, 1, 0);
				
				chosen = 0;
			}
		}
		if(button_check(joy_button)){
			clear_oled();
			if(chosen == 0){
				oled_write_string(3, "Wojak chosen", 8);
			}
			else{
				oled_write_string(3, "Pepe chosen", 8);
			}
			_delay_ms(700);
			return;
		}
	}
}
void play_game(){
	clear_oled();
	calc_offset();
	can_message* msgToReceive;
	uint8_t position = 0;
	while(!(PIND & (1<< PIND5))){ //right button to exit game
		//Sending joystick data to node 2
		send_stick_can();
		//Checking for messages from node 2
		if(can_interrupted()){
			msgToReceive = receive_can_msg(0);
			uint16_t id = msgToReceive->id;
			printf("\r fake id and data: %d  %d \r\n",id, msgToReceive->data[0]);
			printf("\r id and length: %d  %d \r\n",msgToReceive->id, msgToReceive->data_length);
			switch (id){
			case 0x1:
      			// 0x1 means: Goal scored
				clear_oled();
				oled_write_string(3, "GAME OVER!", 8);
				_delay_ms(3500);
				return;
      			break;

			case 0x4:
				// 0x4 means: Motor position
				//clear_oled();
				//character_printer(smol_wojak, 8, 8, (((msgToReceive->data[0]) * (128-40))/100), 24, 0);
				go_to_line(1);
				for (uint8_t i = 0; i < 5; i++){
					go_to_column(position + i);
					oled_write_data(0b00000000);
				}
				position = msgToReceive->data[0] * (128-8)/100;
				for (uint8_t i = 0; i < 5; i++){
					go_to_column(position + i);
					oled_write_data(0b11110000);
				}

				if(msgToReceive->data[1]){
					oled_write_string(3, "SHOT", 8);
				}
				break;
			
			case 0x7:
				// 0x7 means: Time gone by
				oled_write_string(0, msgToReceive->data[0], 8);
				break;
			
			default:
				;
				//oled_write_string(1, "unknown CAN", 8);
			}
		}
	}
	return;
}