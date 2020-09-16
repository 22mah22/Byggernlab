#include "OLED_driver.h"
#include <avr/pgmspace.h>


volatile int fontSize = 8;
const char* const font[] PROGMEM = {font_4x6, font_5x7, font_5x7w, font_8x8};
int current_font = FONT_8X8;


void switch_font(fontType type) {
	current_font = type;
	switch(type){
		case(FONT_4X6):
			fontSize = 4;
		case(FONT_5X7):
			fontSize = 5;
		case(FONT_5X7W):
			fontSize = 5;
		case(FONT_8X8):
			fontSize = 8;
	}
}


int oled_write_char(unsigned char c, oled_position_t* position){
	uint8_t printChar = c-32;
	
	for (int i=0; i < fontSize; i++) {
		write_data(pgm_read_word(&font_8x8[printChar][i]));
		position->col += fontSize;
		//Kan vi skrive utenfor OLED?
	}
	
	return 0;
}
