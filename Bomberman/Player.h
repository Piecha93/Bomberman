#pragma once
#include "Object.h"
#include "Controller.h"

//deklaracja zapowiadajaca
enum BONUS;

class Player :
	public Object
{
	//friend class Bomb;
private:
	//czy zywy?
	bool m_isalive;
	//rysowac status?
	bool m_draw_status;
	//maksymalna ilosc bomb do podlozenia
	int m_bombsquanity;
	//ilosc rzuconych bomb na dany moment
	int m_bombsdroped;
	//sila wybuchu bomb
	int m_bombspower;	
	//nazwa gracza
	string m_name;
	//domyslne wartosci sily wybuchu oraz ilosci bomb
	enum { POWER = 2};
	enum { QUANITY = 1};
	//klasa obslugujaca sterowanie
	Controller m_controll;

public:
	//domyslny konstruktor
	Player(int x = -1, int y = -1, char s = char(1), int quanity = QUANITY, int droped = 0, int power = POWER, bool alive = true, bool status = true, string name = "Default_name")
		: Object(x, y, s), m_bombsquanity(quanity), m_bombsdroped(droped), m_bombspower(power), m_name(name), m_isalive(alive), m_draw_status(status),
		m_controll(0, 0, 0, 0, 0) {  }
	//konstruktor z argumentami
	Player(int x, int y, string name, int up, int down, int left, int right, int bomb)
		: Object(x, y, char(1)), m_bombsquanity(QUANITY), m_bombsdroped(0), m_bombspower(POWER), m_name(name), m_isalive(true), m_draw_status(true),
		m_controll(up, down, left, right, bomb) { }
	//konstruktor kopiujacy
	Player(Player &p);
	//ustawienie imienia i pozycji gracza
	void setPlayer(int x, int y, string name);
	//ustawienie imienia, pozycji gracza i sterowania
	void setPlayer(int x, int y, string name, int up, int down, int left, int right, int bomb);
	//zmiejsza ilosc rzuconych bomb
	void decBombsDroped() { m_bombsdroped--; }
	//zwieksza sile bomb
	void getBonusBombPower() { m_bombspower++; }
	//zwieksza ilosc bomb
	void getBonusBombQuanity() { m_bombsquanity++; }
	//akcesory
	int getBombsPower() { return m_bombspower; }
	string getName() { return m_name; }
	bool isAlive() { return m_isalive; }
	//zabij gracza
	void kill();
	//zwraca kierunek w ktorym gracz idzie
	DIRECTION move();
	//obsluga sterowania
	bool moveDir(DIRECTION dir);
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	bool plantBomb();
	//rysowanie statusu
	void drawStatus(int x);
	void resetDrawStatus() { m_draw_status = true; }
	//porownanie wspolrzednych 2 graczy
	bool operator==(Player & p);

	~Player();
};

