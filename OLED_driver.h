#pragma once


typedef enum{FONT_4X6, FONT_5X7, FONT_5X7W, FONT_8X8} fontType;

typedef struct {
	int row, col;
} oled_position_t;



int oled_write_char(unsigned char c)

