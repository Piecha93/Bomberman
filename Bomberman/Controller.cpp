#include "stdafx.h"
#include "Controller.h"

DIRECTION Controller::readInput()
{
	//pobiera jeden klawisz i zwraca kierunek
	if( GetAsyncKeyState(m_bomb) )
	{
		return BOMB;
	}
	else if( GetAsyncKeyState(m_up) )
	{
		return UP;
	}
	else if( GetAsyncKeyState(m_down) )
	{
		return DOWN;
	}
	else if( GetAsyncKeyState(m_left) )
	{
		return LEFT;
	}	
	else if( GetAsyncKeyState(m_right) )
	{
		return RIGHT;
	}
	//jesli nie wcisnieto zmapowanego klawisza to zwraca pusty
	return NONE;
		
}

//ustawienie mapy kalwiszy
void Controller::setKeys(int up, int down, int left, int right, int bomb)
{
	m_up = up;
	m_down = down;
	m_left = left;
	m_right = right;
	m_bomb = bomb;
}
Controller::~Controller()
{
}
