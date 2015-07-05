#pragma once

enum MENU_STATUS { START_GAME, MAIN, INSTRUCTIONS, SETTINGS, EXIT};
class Menu
{
private:
	//pozycja w menu
	int m_position;
	//tablice z tekstem odpowiednich menu
	string menuStart[4];
	string menuInstructions[7];

	MENU_STATUS drawMain();
	MENU_STATUS drawInstructions();
	MENU_STATUS drawSettings();
public:
	Menu();
	MENU_STATUS drawMenu();
	~Menu();
};

