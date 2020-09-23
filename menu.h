#pragma once
#include <stdint>

typedef struct
{
    char labels[8][16];

    struct menu* links[8];

    uint8_t selected = 0;
} menu;

menu* new_menu(menu* parent);

void write_menu_to_screen(menu* currentMenu);

void change_menu(menu* currentMenu);

void invert_selected(menu* currentMenu);

void change_selected(menu* currentMenu);