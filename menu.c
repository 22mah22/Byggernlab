#include "menu.h"
#include "OLED_driver.h"

volatile menu* currentMenu;

menu* new_menu(menu* parent){
    menu* menu = malloc(sizeof(menu));
	for(unsigned int i = 0; i < 8, i++){
        menu->links[i] = NULL;
    }
    *(menu->selected) = 0;
	return menu;
}

void write_menu_to_screen(menu* currentMenu){
    for(uint8_t i = 0; i < 8; i++){
        go_to_line(i);
        oled_write_string(currentMenu->labels[i])
    }
}

void change_menu(menu* currentMenu){
    write_menu_to_screen(currentMenu->links[currentMenu->selected])
}

void invert_selected(menu* currentMenu){

}

void change_selected(menu* currentMenu){

}

void test_menu(){
    currentMenu = new_menu(NULL);
    write_menu_to_screen(currentMenu);