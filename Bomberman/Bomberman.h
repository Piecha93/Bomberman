#pragma once

//deklaracje zapowiadajace
class Game;
class Menu;

class Bomberman
{
private:
	Game * m_game;
	Menu * m_menu;
public:
	Bomberman() : m_game(nullptr), m_menu(nullptr) {}
	void run();
	~Bomberman();
};

