/**
 * @file
 * @brief Driver module for handling data transmission over the CAN-bus
 */

#pragma once
#include <stdint.h>
#include "joystick_driver.h"
//#include "protagonists.h"
#include <util/delay.h>

/**
 * @brief Struct for content in a menu page
 * labels are names of options, one for each line
 * links are references to submenues (linked list)
 * f are function pointers as an option to submenues
 * selected keeps track of the selected option for each menu
 */
typedef struct
{
	char* labels[8];

	struct menu* links[8];

	void (*f[8]) (void);

	uint8_t selected;
	
} menu;


/**
 * @brief Function to create a new menu page. 
 * @warning Uses Malloc to allocate space for the menu in memory
 * @param parent uses a pointer to its parent in order to create a "back" - option
 */
menu* new_menu(menu* parent);

/**
 * @brief Function to write the current menu to screen
 * @param menuPointer pointer to current screen
 */
void write_menu_to_screen(menu* menuPointer);

/**
 * @brief Function to change the menu
 * @param menuHead is a pointer to our current placement in the linked list
 * @param next_menu is a pointer to the menu we are navigating to
 */
void change_menu(menu* next_menu, menu** menuHead);

/**
 * @brief Function to invert the selected row. Selected row is tracked by the "seleced" variable in the struct
 * @param menuPointer pointer to current screen
 */
void invert_selected(menu* menuPointer);

/**
 * @brief Function to change which option in a menu is selected
 * @param menuHead pointer to current menu
 * @param d joystick direction used to change the selected item according to user input
 */
void change_selected(menu** menuHead, DIRECTION d);

/**
 * @brief Function to check if the joystick button is pressed
 * @param menuHead pointer to current active menu
 */
void button_pressed(menu** menuHead);

/**
 * @brief Function to start our pretetermined menusystem
 */
void launch_menusystem();

/**
 * @brief Function that prints a familiar face to the OLED
 */
void wojakprinter();

/**
 * @brief Function to write "hello world" to the OLED
 */
void hello_world();

/**
 * @brief Function to let you choose between our two characters.
 * The choice gets saved to SRAM and enables high-score tracking
 */
void choose_character();

/**
 * @brief Function to initialize ping-pong game
 * uses CAN to send joystick info over to node 2
 * receives feedback over CAN and displays it on the OLED
 */
void play_game();

/**
 * @brief Function to calibrate joystick for offset.
 * Gives user clear instructions
 */
void calibrate();

/**
 * @brief Function to set PID regulator on node 2 to easy mode over CAN
 */
void set_easy();

/**
 * @brief Function to set PID regulator on node 2 to medium mode over CAN
 */
void set_medium();

/**
 * @brief Function to set PID regulator on node 2 to hard mode over CAN
 */
void set_hard();

/**
 * @brief Function to credit the creators of the game on the OLED.
 */
void show_credits();

/**
 * @brief Function to show current high scores for both characters
 * uses information from SRAM
 */
void hiscore();

/**
 * @brief Function to set high score values for both characters to 0 in SRAM
 */
void reset_scores();

/**
 * @brief Function to launch a small minigame that lets you test your reaction time
 * sends a start and a stop signal to node 2 which has the timer implemented. 
 * you lose if you press too early.
 */
void reaction_test();