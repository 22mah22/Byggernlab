#include "OLED_driver.h"
#include "fonts.h"

void oled_write_command(char c)
{
	volatile char *ext_ram = (char *) 0x1000;
	ext_ram[0] = c;
}
void oled_write_data(char c)
{
	volatile char *ext_ram = (char *) 0x1200;
	ext_ram[0] = c;
}

void oled_init(amap* atmelMap){
	oled_write_command(0xae); //display off
	oled_write_command(0xa1); //segment remap
	oled_write_command(0xda); //common pads hardware: alternative
	oled_write_command(0x12);
	oled_write_command(0xc8); //common output scan direction:com63-com0
	oled_write_command(0xa8); //multiplex ration mode:63
	oled_write_command(0x3f);
	oled_write_command(0xd5); //display divide ratio/osc. freq. mode
	oled_write_command(0x80);
	oled_write_command(0x81); //contrast control
	oled_write_command(0x50);
	oled_write_command(0xd9); //set pre-charge period
	oled_write_command(0x21);
	oled_write_command(0x20); //set memory addressing mode
	oled_write_command(0x02);                                    //page addressing mode
	oled_write_command(0xdb); //VCOM deselect level mode
	oled_write_command(0x30);
	oled_write_command(0xad); //master configuration
	oled_write_command(0x00);
	oled_write_command(0xa4); //out follows RAM content
	oled_write_command(0xa6); //set normal display
	oled_write_command(0xaf); //display on
}

void go_to_line(amap* atmelMap, uint8_t line){
	oled_write_command(0xB0 + line);
}

void go_to_column(amap* atmelMap, uint8_t column){
	
	oled_write_command(0x00 + (column%16));
	oled_write_command(0x10 + (column/16));
}

void oled_start_write_at(amap* atmelMap, uint8_t page, uint8_t lowerCol, uint8_t upperCol){
	atmelMap->OLED_CMD[1] = 0xB1;
	atmelMap->OLED_CMD[1] = 0x00;
	atmelMap->OLED_CMD[1] = 0x10;
}
void oled_write(amap* atmelMap){
	atmelMap->OLED_DATA[1] = 0x0F;
}

void clear_oled(amap* atmelMap){
	for(int i = 0; i < 8 ; i++){
		go_to_line(atmelMap, i);
		
		go_to_column(atmelMap, 0);
		for(int j = 0; j < 128; j++){
			
			oled_write_data(0x00);
		}
	}
}

void oled_write_string(char* c){
	
	for (int i=0; i < strlen(c); i++) {
		oled_write_char8(c[i]);
	}
	
}

/*void oled_write_char_using_font(char c, fontType f){
	uint8_t character = c-32;
	
	for (int i=0; i < 8; i++) {
		oled_write_data(pgm_read_byte(&(f[character][i])));
	}
	
}*/

void oled_write_char8(char c){
	uint8_t character = c-32;
	
	for (int i=0; i < 8; i++) {
		oled_write_data(pgm_read_byte(&(font8[character][i])));
	}
	
}