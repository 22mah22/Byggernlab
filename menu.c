#include "menu.h"
#include "OLED_driver.h"

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
    menu mainMenu;
    menu* menu_p = &mainMenu;

    menu secondMenu;
    menu_p->links[1] = &secondMenu;

    menu_p->labels[0] = "Menu option 1";
    menu_p->labels[1] = "Menu option 2";

    while(1){
        if(!(PINB & (1<<PINB1))){
            change_menu(menu_p->links[menu_p->selected])
        }
    }
}