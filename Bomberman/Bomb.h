#pragma once
#include "Object.h"

class Player;

class Bomb :
	public Object
{
private:
	//sila wybuchu
	int m_power;
	//czas pozostaly do wybuchu w ms
	int m_time;
	//czy wybuchlo?
	bool m_bang; 
	//wskaznik na gracza ktory polozyl bombe
	Player * m_p;
	//stala - domyslny czas wybuchu
	enum { TIME = 3000 };
public:
	//konstruktor domyslny
	Bomb(int x = -1, int y = -1, char s = '*', int time = TIME, int power = 3) : Object(x, y, s), m_time(time), m_power(power) {}
	//konstruktor z argumentami
	Bomb(int x, int y, Player* p);

	//akcesory
	bool getBangStatus() { return m_bang; }
	int getPower() { return m_power; }
	//obniza czas do wybuchu bomby o czas time (ms)
	void decTimer(int time) { m_time -= time; }
	//aktualizuje czas do wybuchu
	virtual void update(int time);
	//rysuje bombe
	virtual void draw();
	//destruktor
	virtual ~Bomb();
};

