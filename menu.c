#include "menu.h"
#include "OLED_driver.h"

volatile menu* currentMenu;

menu* new_menu(menu* parent){
    menu* menu = malloc(sizeof(menu));
	for(unsigned int i = 0; i < 8, i++){
        menu->links[i] = NULL;
    }
    *(menu->selected) = 0;
    menu->links[7] = parent;
    menu->labels[7] = "<- Back";
	return menu;
}

void write_menu_to_screen(menu* menuPointer){
    for(uint8_t i = 0; i < 8; i++){
        go_to_line(i);
        oled_write_string(menuPointer->labels[i]);
    }
}

void change_menu(menu* menuPointer){
    write_menu_to_screen(menuPointer->links[menuPointer->selected]);
    currentMenu = menuPointer;
}

void invert_selected(menu* menuPointer){

}

void change_selected(menu* menuPointer){
    //if joystick opp: Selected -= 1
    //if joystick ned: Selected += 1
    // if selected = -1, selected = 7
    //if selected = 8, selected = 0
}

void test_menu(){
    currentMenu = new_menu(NULL);
    write_menu_to_screen(currentMenu);