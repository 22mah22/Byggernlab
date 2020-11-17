/**
 * @file
 * @brief Driver module for handling writing to the OLED display
 */

#pragma once
#include "DEFINITIONS.h"
/**
 * @brief array to keep track of which pixels on the screen are on and which are off
uint8_t oled_array[8][100];

/**
 * @brief Function to write commands to OLED display. Commands go in a different memory location than data.
 * @param c byte to write
 */
void oled_write_command(char c);

/**
 * @brief Function to write data to OLED display. Data goes in a different memory location than commands.
 * @param c byte to write
 */
void oled_write_data(char c);

/**
 * @brief Function to initialize OLED display. Writes a series of commands to enable use of this modules other functions,
 */
void oled_init();

/**
 * @brief Function to select a line to write to
 * @param line to write. There are 8 lines each consisting of one byte.
 */
void go_to_line(uint8_t line);

/**
 * @brief Function to select a column to write to
 * @param column to write. There are 128 colums.
 */
void go_to_column(uint8_t column);


void oled_start_write_at(amap* atmelMap, uint8_t page, uint8_t lowerCol, uint8_t upperCol);

void oled_write(amap* atmelMap);

/**
 * @brief Function to set all pixels black
 */
void clear_oled();

void clear_oled_new();

/**
 * @brief Function to write a string at a selected line using a selected font.
 * @param startline line to write at
 * @param c string to write
 * @param n font to use. 4, 5 or 8 are the usable options. They describe their own size.
 */
void oled_write_string(uint8_t startline, char* c, uint8_t n);

/**
 * @brief Function to write a black string on a white background at a selected line using a selected font.
 * @param startline line to write at
 * @param c string to write
 * @param n font to use. 4, 5 or 8 are the usable options. They describe their own size.
 */
void oled_write_string_inverted(uint8_t startline, char* c, uint8_t n);

/**
 * @brief Function to write a char using a selected font.
 * @param c char to write
 * @param n font to use. 4, 5 or 8 are the usable options. They describe their own size.
 */
void oled_write_char_using_font(char c, uint8_t n);

/**
 * @brief Function to write a black char on a white background using a selected font.
 * @param c char to write
 * @param n font to use. 4, 5 or 8 are the usable options. They describe their own size.
 */
void oled_write_inverted_char_using_font(char c, uint8_t n);

/**
 * @brief Function to write a char using the biggest font
 * @param c char to write
 */
void oled_write_char8(char c);

/**
 * @brief Fancy function to write a bit matrix where height and width is divisible by 8 to the OLED.
 * Any picture can be converted to a 0/1 matrix using internet tools and therefore be printed to the screen.
 * @param arr bit matrix to write
 * @param width width of the matrix (divisible by 8)
 * @param height height of the matrix (divisible by 8)
 * @param x_offset how far from the left border of the screen to place picture
 * @param y_offset how far from the top of the screen to place picture
 * @param inverted 1 for an inverted picture, 0 for white on black
 */
void character_printer(uint8_t arr[], int width, int height, uint8_t x_offset, uint8_t y_offset, uint8_t inverted);

/**
 * @brief Function to draw on the screen using the sliders
 * @param l_slider left slider value
 * @param r_slider right slider value
 * @param write whether to write white or black. 1 for "pencil", 0 for "rubber"
 */
void oled_drawing(uint8_t l_slider, uint8_t r_slider, uint8_t write);

/**
 * @brief Function to null out the array that keeps track of the screen pixels
 */
void reset_oled_array();

/**
 * @brief Function to draw on the screen and store the resulting "painting" in sram instead of a bit matrix
 * Otherwise equivalent to oled_drawing.
 * @param sram sram location in memory
 */
void oled_drawing_sram(char* sram, uint8_t l_slider, uint8_t r_slider, uint8_t write);

/**
 * @brief Function to null out the array that keeps track of the screen pixels in the sram
 */
void reset_oled_array_sram(char* sram);
