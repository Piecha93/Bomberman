#include "stdafx.h"
#include "Player.h"

//konstruktor kopiujacy
Player::Player(Player &p) : Object(p), m_controll(p.m_controll)
{
	m_bombsdroped = p.m_bombsdroped;
	m_bombspower = p.m_bombspower;
	m_bombsquanity = p.m_bombsquanity;
	m_name = p.m_name;
}

//ustawienie imienia i pozycji gracza
void Player::setPlayer(int x, int y, string name)
{
	Object::setxy(x, y);
	m_name = name;
}

//ustawienie imienia, pozycji gracza i sterowania
void Player::setPlayer(int x, int y, string name, int up, int down, int left, int right, int bomb)
{
	setPlayer(x, y, name);
	m_controll.setKeys(up, down, left, right, bomb);
}

//obsluga sterowania
bool Player::moveDir(DIRECTION dir)
{
	switch( dir )
	{
		case UP:
			return moveUp();
			break;
		case DOWN:
			return moveDown();
			break;
		case LEFT:
			return moveLeft();
			break;
		case RIGHT:
			return moveRight();
			break;
		default:
			break;
	};
	return false;
}
bool Player::moveUp()
{
	if( m_isalive )
	{
		sety(gety() - 1);
		resetDraw();
		return true;
	}
	return false;
}
bool Player::moveDown()
{
	if( m_isalive )
	{
		sety(gety() + 1);
		resetDraw();
		return true;
	}
	return false;
}
bool Player::moveLeft()
{
	if( m_isalive )
	{
		setx(getx() - 1);
		resetDraw();
		return true;
	}
	return false;
}
bool Player::moveRight()
{
	if( m_isalive )
	{
		setx(getx() + 1);
		resetDraw();
		return true;
	}
	return false;
}

//zwraca true jesli gracz ma jakies bomby
bool Player::plantBomb()
{
	if( m_isalive )
	{
		if( m_bombsdroped < m_bombsquanity )
		{
			m_bombsdroped++;
			return true;
		}
	}
	return false;
}

//zabija gracza
void Player::kill()
{
	m_isalive = false;
	m_draw = false;
	m_draw_status = true;
	setxy(0, 0);
}

//zwraca kierunek ruchu
DIRECTION Player::move()
{
	DIRECTION tmp = m_controll.readInput();
	return tmp;
}

//rysuje status gracza
void Player::drawStatus(int x)
{
	if( m_draw_status )
	{
		if( m_isalive )
			cout << getName() << " Bomby: " << m_bombsquanity << " Sila bomb: " << m_bombspower;
		else
			cout << getName() << " nie zyje :(                       ";
		m_draw_status = false;
	}
}

//porownuje wspolrzedne
bool Player::operator==(Player & p)
{
	if( getx() == p.getx() && gety() == p.gety() )
		return true;
	return false;
}

Player::~Player()
{
}
