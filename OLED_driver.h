#pragma once
#include "DEFINITIONS.h"

//typedef enum{font8, font5, font4} fontType;

void oled_write_command(char c);

void oled_write_data(char c);

void oled_init();

void go_to_line(uint8_t line);

void go_to_column(uint8_t column);

void oled_start_write_at(amap* atmelMap, uint8_t page, uint8_t lowerCol, uint8_t upperCol);

void oled_write(amap* atmelMap);

void clear_oled();

void clear_oled_new();

void oled_write_string(uint8_t startline, char* c, uint8_t n);

void oled_write_string_inverted(uint8_t startline, char* c, uint8_t n);

void oled_write_char_using_font(char c, uint8_t n);

void oled_write_inverted_char_using_font(char c, uint8_t n);

void oled_write_char8(char c);

void character_printer(uint8_t arr[], int width, int height, uint8_t x_offset, uint8_t y_offset, uint8_t inverted);

void oled_drawing(uint8_t l_slider, uint8_t r_slider, uint8_t write);

void reset_oled_array();

void oled_drawing_sram(char* sram, uint8_t l_slider, uint8_t r_slider, uint8_t write);

void reset_oled_array_sram(char* sram);

uint8_t oled_array[8][100];