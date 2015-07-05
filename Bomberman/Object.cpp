#include "stdafx.h"
#include "Object.h"

//konstruktor kopiujacy
Object::Object(Object & obj)
{
	m_draw = obj.m_draw;
	m_sign = obj.m_sign;
	m_x = obj.m_x;
	m_y = obj.m_y;
}

//zamiana wspolrzednych z innym obiektem
void Object::swapCoord(Object *obj)
{
	int tmpy = m_y;
	int tmpx = m_x;
	m_y = obj->m_y;
	m_x = obj->m_x;
	obj->m_y = tmpy;
	obj->m_x = tmpx;
}

//rysuj
void Object::draw()
{
	if( m_draw )
	{
		//ustawianie pozycji rysowania
		COORD c;
		c.X = m_x;
		c.Y = m_y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

		cout << m_sign;
		m_draw = false;
	}
}

//porownanie wspolrzednych obiektow
bool Object::operator==(Object & p)
{
	if( getx() == p.getx() && gety() == p.gety() )
		return true;
	return false;
}

Object::~Object()
{
}