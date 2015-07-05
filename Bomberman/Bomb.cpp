#include "stdafx.h"
#include "Bomb.h"
#include "Player.h"

//konstruktor z argumentami
Bomb::Bomb(int x, int y, Player* p) : Object(x, y, '*')
{
	m_power = p->getBombsPower();
	m_time = TIME;
	m_bang = false;
	m_p = p;
}

//aktualizuje czas do wybuchu
void Bomb::update(int time)
{
	m_time -= time;
	if( !m_bang )
	{
		if( m_time < 0 )
		{
			m_bang = true;
			//zwraca graczowi bombe
			m_p->decBombsDroped();
		}
	}
}

//rysuje
void Bomb::draw()
{
	//ustawienie koloru w konsoli
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	Object::draw();
}

//destruktor
Bomb::~Bomb()
{
	m_p = nullptr;
}
