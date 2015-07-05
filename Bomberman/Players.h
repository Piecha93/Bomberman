#pragma once
#include <vector>

//deklaracje zapowiadaje
class Player;
class Field;
enum DIRECTION;

//typdef iteratora
typedef std::vector<Player*>::iterator player_iter;

class Players
{
private:
	//liczba graczy
	int m_numplayers;
	//vektor przechowujacy graczy
	std::vector<Player*> m_playersArray;
public:
	//konstruktor z parametrami
	Players(int numplayers, int sizex, int sizey);
	//tworzy wszystkich graczy
	bool createPlayers(int numplayers, int sizex, int sizey);
	//rysuje wszystkich graczy
	void draw();
	//rysuje status wszystkich graczy
	void drawStatus(int x);
	//zwalnia pamiec i usuwa tablice graczy
	bool deleteArray();
	//pobiera akcje graczy
	void getEvents(Field * f);
	//ruch gracza
	void move(Player* p, DIRECTION dir, Field * f);
	//zwraca iteratory na poczatek i koniec tablicy
	player_iter getIteratorBegin() { return m_playersArray.begin(); }
	player_iter getIteratorEnd() { return m_playersArray.end(); }
	//sprawdza kto wygral
	int checkWinner();
	//akcesory
	//destruktor
	~Players();
};

