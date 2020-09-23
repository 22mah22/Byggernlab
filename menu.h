#pragma once
#include <stdint>

typedef struct
{
    char labels[8][16];

    menu* links[8] = {
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr
    };

    uint8_t selected = 0;
} menu;

void write_menu_to_screen(menu* currentMenu);

void change_menu(menu* currentMenu);

void invert_selected(menu* currentMenu);

void change_selected(menu* currentMenu);