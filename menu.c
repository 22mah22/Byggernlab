#include "menu.h"
#include "OLED_driver.h"
#include <string.h>
#include "protagonists.h"
#include "joystick_driver.h"
//#include "menuconfigs.h"
#include "can_driver.h"
#include <stdlib.h>

volatile char * sram = (char *) 0x1800;

char* string_list[] = {
	"Option 1",
	"Option 2",
	"Option 3",
	"",
	"",
	"",
	"",
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
		oled_write_string(i, menuPointer->labels[i], 5);
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
	oled_write_string_inverted((menuPointer->selected), menuPointer->labels[(menuPointer->selected)], 5);
}

void change_selected(menu** menuHead, DIRECTION d){
	if(d == UP){
		((*(menuHead))->selected)--;
		while(((*(menuHead))->labels[((*(menuHead))->selected)]) == ""){
			((*(menuHead))->selected)--;
		}
	}
	if(d == DOWN){
		((*(menuHead))->selected)++;
		while(((*(menuHead))->labels[((*(menuHead))->selected)]) == ""){
			((*(menuHead))->selected)++;
		}
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
		menu* submenu2 = new_menu(mainMenu);
		menu* difficulties = new_menu(mainMenu);
		
		mainMenu->labels[0] = "Play ping-pong";
		mainMenu->f[0] = play_game;

		mainMenu->labels[1] = "Graphics";

		mainMenu->labels[2] = "Characters";
		mainMenu->links[2] = submenu2;

		mainMenu->labels[3] = "Calibrate stick";
		mainMenu->f[3] = calibrate;

		mainMenu->labels[4] = "Difficulty";
		mainMenu->links[4] = difficulties;
		difficulties->labels[0] = "easy";
		difficulties->f[0] = set_easy;
		difficulties->labels[1] = "medium";
		difficulties->f[1] = set_medium;
		difficulties->labels[2] = "hard";
		difficulties->f[2] = set_hard;

		mainMenu->labels[5] = "Reaction test";
		mainMenu->f[5] = reaction_test;

		mainMenu->labels[6] = "Draw a wojak";
		mainMenu->f[6] = wojakprinter;
		mainMenu->labels[7] = "Credits";
		mainMenu->f[7] = show_credits;

		submenu2->labels[0] = "Choose character";
		submenu2->f[0] = choose_character;
		submenu2->labels[1] = "Hiscores";
		submenu2->f[1] = hiscore;
		submenu2->labels[2] = "Reset scores";
		submenu2->f[2] = reset_scores;
		submenu2->labels[4] = "";
		submenu2->labels[5] = "";
		submenu2->labels[6] = "";
		
		
	headPointer = &mainMenu;
	write_menu_to_screen(*headPointer);
	const int *BASE = 0x1000;
	const int *ADC = 0x1401;
	volatile amap* atmelMap = (amap*) BASE;
	 
	calc_offset();

	//RUN
	while(1){
		
		update_adc_values();
		
		uint8_t left_button = PIND & (1<< PIND4);
		uint8_t right_button = PIND & (1<< PIND5);
		uint8_t joy_button = PINB & (1<< PINB1);
	
	
		//_delay_ms(1);
		DIRECTION current_dir = joystick_direction(current_dir);
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
	oled_write_string(0, "Hello world!", 5);
	oled_write_string(7, "Joystick-return", 5);
	_delay_ms(1000);
	while((PINB & (1<< PINB1))){}
	return;
}

void choose_character(){
	clear_oled();
	oled_write_string(0, "CHOOSE!", 5);

	//INVERT LEFT PICTURE
	character_printer(wojak, 64, 40, 0, 1, 1);
	character_printer(pepe, 64, 40, 64, 1, 0);
	
	uint8_t chosen = 0;
	
	while(1){
		update_adc_values();
		
		uint8_t left_button = PIND & (1<< PIND4);
		uint8_t right_button = PIND & (1<< PIND5);
		uint8_t joy_button = PINB & (1<< PINB1);
	
		DIRECTION current_dir = joystick_direction(current_dir);
		if(current_dir != NEUTRAL && current_dir != WAITING){
			if (current_dir == RIGHT){
				//INVERT RIGHT PICTURE
				clear_oled();
				oled_write_string(0, "CHOOSE!", 5);
				character_printer(wojak, 64, 40, 0, 1, 0);
				character_printer(pepe, 64, 40, 64, 1, 1);
				
				chosen = 1;
			}
			//INVERT LEFT PICTURE
			else if (current_dir == LEFT){
				clear_oled();
				oled_write_string(0, "CHOOSE!", 5);
				character_printer(wojak, 64, 40, 0, 1, 1);
				character_printer(pepe, 64, 40, 64, 1, 0);
				
				chosen = 0;
			}
		}
		if(button_check(joy_button)){
			clear_oled();
			if(chosen == 0){
				oled_write_string(3, "Wojak chosen", 5);
				//save selected character in sram
				sram[0] = 0;
			}
			else{
				oled_write_string(3, "Pepe chosen", 5);
				//save selected character in sram
				sram[0] = 1;
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
			switch (id){
			case 0x1:
      			// 0x1 means: Goal scored
				clear_oled();
				go_to_column(10);
				oled_write_string(3, "GAME OVER!", 5);

				if(sram[0] == 0){ //wojak is selected
					sram[1] = msgToReceive->data[0];
					sram[2] = msgToReceive->data[1];
				}
				else if(sram[0 == 1]){ //pepe is selected
					sram[3] = msgToReceive->data[0];
					sram[4] = msgToReceive->data[1];
				}
				uint16_t seconds = msgToReceive->data[0] + (msgToReceive->data[1] << 4);
				char buffer[6];
				sprintf (buffer, "%u", seconds);

				go_to_column(10);
				oled_write_string(4, "Your score:",5);
				oled_write_string(5, buffer,8);
				_delay_ms(3500);
				return;
      			break;

			case 0x4:
				// 0x4 means: Motor position
				//clear_oled();
				//character_printer(smol_wojak, 8, 8, (((msgToReceive->data[0]) * (128-40))/100), 24, 0);
				go_to_line(8);
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
					oled_write_string(3, "SHOT", 5);
				}
				break;
			
			case 0x7:
				// 0x7 means: Time gone by
				oled_write_string(0, msgToReceive->data[0], 5);
				break;
			
			default:
				;
				//oled_write_string(1, "unknown CAN", 8);
			}
		}
	}
	return;
}

void calibrate(){
	clear_oled();
	go_to_line(0);
	go_to_column(10);
	oled_write_string(0, "Please let go of stick", 5);
	oled_write_string(3, "Calibrating in:", 5);
	_delay_ms(1500);
	oled_write_string(4, "3", 8);
	_delay_ms(1500);
	oled_write_string(4, "2", 8);
	_delay_ms(1500);
	oled_write_string(4, "1", 8);
	_delay_ms(1500);
	calc_offset();
	clear_oled();
	go_to_line(0);
	go_to_column(10);
	oled_write_string(0, "Joystick calibrated", 5);
	_delay_ms(1500);
	return;
}

void set_easy(){
	send_difficulty_can(1);
	clear_oled();
	go_to_line(0);
	go_to_column(10);
	oled_write_string(0, "Difficulty set to easy", 5);
	_delay_ms(1500);
	return;
}

void set_medium(){
	send_difficulty_can(2);
	clear_oled();
	go_to_line(0);
	go_to_column(10);
	oled_write_string(0, "Difficulty set to medium", 5);
	_delay_ms(1500);
	return;
}

void set_hard(){
	send_difficulty_can(3);
	clear_oled();
	go_to_line(0);
	go_to_column(10);
	oled_write_string(0, "Difficulty set to hard", 5);
	_delay_ms(1500);
	return;
}

void show_credits(){
	clear_oled();
	go_to_column(10);
	oled_write_string(0, "MADE BY:", 5);
	go_to_column(10);
	oled_write_string(2, "Bendik Lovlie", 5);
	go_to_column(10);
	oled_write_string(3, "Magne Hovdar", 5);
	go_to_column(10);
	oled_write_string(4, "Thomas Nyhus", 5);
	go_to_column(10);
	oled_write_string(6, "TTK4155", 5);
	go_to_column(10);
	oled_write_string(7, "Autumn 2020, NTNU", 5);
	_delay_ms(1500);
	return;
}

void hiscore(){
	clear_oled();
	go_to_column(10);
	uint16_t seconds = sram[1] + (sram[2] << 4);
	char buffer[6];
	sprintf(buffer, "%u", seconds);
	oled_write_string(1, "wojak high score:", 5);
	go_to_column(10);
	oled_write_string(2, buffer, 5);
	seconds = sram[3] + (sram[4] << 4);
	sprintf(buffer, "%u", seconds);
	go_to_column(10);
	oled_write_string(4, "pepe high score:", 5);
	go_to_column(10);
	oled_write_string(5, buffer, 5);
	_delay_ms(1500);
	return;
}

void reset_scores(){
	for(int i = 1; i < 5; i++){
		sram[i] = 0;
	}
	clear_oled();
	go_to_column(10);
	oled_write_string(0, "Hiscores deleted", 5);
	_delay_ms(1500);
	return;
}

void reaction_test(){
	clear_oled();
	go_to_column(10);
	oled_write_string(0, "If left lights up,", 5);
	go_to_column(10);
	oled_write_string(1, "click left.", 5);
	go_to_column(10);
	oled_write_string(2, "If right lights up,", 5);
	go_to_column(10);
	oled_write_string(3, "click right.", 5);
	_delay_ms(2500);

	uint8_t trigger = 0;
	uint8_t side = 0;
	while(!(button_check(PIND & (1<< PIND4)) || button_check(PIND & (1<< PIND5)))){
		//0.1s interval start time
		_delay_ms(100);
		uint8_t num = (rand() % (30 + 1));

		//Random start time of game
		if(num == 10){
			send_reaction_start_can();
			trigger = 1;
			if(!(num % 2)){
				clear_oled();
				for(int row = 0; row < 8; row++){
					for (int col = 0; col <64; col++){
						go_to_column(col);
						go_to_line(row);
						oled_write_data(0b11111111);
					}
				}
				side = 1;
			}
			else{
				clear_oled();
				for(int row = 0; row < 8; row++){
					for (int col = 64; col <128; col++){
						go_to_column(col);
						go_to_line(row);
						oled_write_data(0b11111111);
					}
				}
				side = 2;
			}
			//react instantly to button presses
			while(!(button_check(PIND & (1<< PIND4)) || button_check(PIND & (1<< PIND5)))){
				;//ensures we avoid 100ms wait time when we react
			}
		}
	}
	if(trigger == 0){
	clear_oled();
	go_to_column(10);
	oled_write_string(0, "Fail. Too early.", 5);
	_delay_ms(1500);
	return;
	}
	//else if button corresponds with lit up side of screen
	else if(((side == 1) && (PIND & (1<< PIND4))) || ((side == 2) && (PIND & (1<< PIND5)))){
		clear_oled();
		can_message* msgToReceive;
		int ms = 0;
		uint8_t id = 0;
		char buffer[6];
		while(1){
			send_reaction_stop_can();
			_delay_ms(50);
			msgToReceive = receive_can_msg(0);
			id = msgToReceive->id;
			if(id == 0x2){
				ms = msgToReceive->data[0] + (msgToReceive->data[1] << 8);
				printf("asdgsdfg %d", ms);
				go_to_column(10);
				oled_write_string(1, "You reaction time:", 5);
				go_to_column(10);
				sprintf(buffer, "%u", ms);
				oled_write_string(2, buffer, 5);
				oled_write_string(3, " milliseconds", 5);
				_delay_ms(2500);
				return;
			}
		}
	}
	else{
		clear_oled();
		go_to_column(10);
		oled_write_string(0, "Something went wrong", 5);
		_delay_ms(1500);
	}
	return;
}