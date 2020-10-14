# include "menu.h"
# include "menuconfigs.h"


menu* setup_testmenu(){

	static menu* mainMenu;
	mainMenu = new_menu(NULL);
	menu* submenu = new_menu(mainMenu);
	menu* submenu_5 = new_menu(mainMenu);
	
	mainMenu->labels[0] = "Demo of a submenu";
	mainMenu->labels[1] = "Choose your character";
    mainMenu->f[1] = choose_character;
	mainMenu->labels[2] = "";
	mainMenu->labels[3] = "Write a greeting";
	mainMenu->labels[4] = "Default submenu";
	mainMenu->labels[5] = "";
	mainMenu->labels[6] = "";
	mainMenu->labels[7] = "";
	mainMenu->links[0] = submenu;
	mainMenu->links[4] = submenu_5;
	
	submenu->labels[0] = "Do nothing";
	submenu->labels[1] = "Loaf around";
	submenu->labels[2] = "List of funny women";
	submenu->labels[3] = "Draw a wojak";
	submenu->f[3] = wojakprinter;
	submenu->labels[4] = "";
	submenu->labels[5] = "";
	submenu->labels[6] = "";

    return mainMenu;
}

menu* setup_blankmenu(){
    menu* mainMenu;
	mainMenu = new_menu(NULL);
    return mainMenu;
}
