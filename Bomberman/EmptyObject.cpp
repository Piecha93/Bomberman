#include "stdafx.h"
#include "EmptyObject.h"

//rysowanie
void EmptyObject::draw()
{
	if( m_draw )
	{
		//ustawienie wspolrzednych w konsoli
		COORD c;
		c.X = getx();
		c.Y = gety();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		//jesli nie plonie ustaw kolor przezroczysty
		if( !m_burn )
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_INTENSITY - 1) | 0);
			cout << getSign();
		}
		//jesli plonie ustaw kolor i tlo czerwone
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | BACKGROUND_RED);
			cout << " ";
		}
		//ustawienie draw na false aby niepotrzebnie nie rysowac tego samego wiele razy
		m_draw = false;
	}
}

//podpalenie obiektu (uzywane podczas wybuchu)
void EmptyObject::setFire()
{
	m_timeToBurn = BURNTIME;
	m_burn = true;
}

//uaktualnienie czasu palenia
void EmptyObject::update(int time)
{
	if( m_burn )
	{
		m_timeToBurn -= time;
		if( m_timeToBurn < 0 )
			m_burn = false;
		resetDraw();
	} 
}

EmptyObject::~EmptyObject()
{
}