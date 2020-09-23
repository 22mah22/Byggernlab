#include "menu.h"
#include "OLED_driver.h"

void write_menu_to_screen(menu* currentMenu){
	for(uint8_t i = 0; i < 8; i++){
		oled_write_string(i, currentMenu->labels[i], 8);
	}
}

void change_menu(menu* currentMenu){
	write_menu_to_screen(currentMenu->links[currentMenu->selected]);
}

void invert_selected(menu* currentMenu){

}

void change_selected(menu* currentMenu){

}

void test_menu(){
	
}