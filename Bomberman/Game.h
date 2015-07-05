#pragma once

//deklaracje zapowiadajaace
class Field;
class Players;

class Game
{
private:
	//wskaznik na klase obslugujace mape
	Field * m_field;
	//wskaznik na klase obslugujaca graczy
	Players * m_players;
	//czy plansze poprawnie zainicjalizowano?
	bool m_initialized;
	//domyslne ustawienia
	enum { NUMPLAYERS = 4, SIZEX = 21, SIZEY = 21 };
public:
	//domyslny konstruktor
	Game() : m_initialized(false), m_field(nullptr), m_players(nullptr) { }
	//inicjalizacja gry (plansza, gracze)
	bool initGame();
	bool initGame(int numplayers);
	bool initGame(int x, int y, int m_numplayers);	
	//resetuje wszystkie ustawienia do wartosci domyslnyych
	void resetGame();
	//pobiera informacje o przycisnietych klawiszach
	void getInput();
	//uaktualnia gre
	void update(int time);
	//sprawdza czy ktos nie wygral
	bool checkWinner();
	//rysuje
	void draw();
	~Game();
};

