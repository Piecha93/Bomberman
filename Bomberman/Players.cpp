#include "stdafx.h"
#include "Player.h"
#include "Players.h"
#include "Field.h"
#include "Object.h"
#include "EmptyObject.h"
#include "HardStone.h"
#include "Stone.h"
#include "Bomb.h"
#include "Bonus.h"

#include <vector>

//konstruktor z parametrami
Players::Players(int numplayers, int sizex, int sizey)
{
	createPlayers(numplayers, sizex, sizey);
}

//tworzy wszystkich graczy
bool Players::createPlayers(int numplayers, int sizex, int sizey)
{
	if( numplayers > 0 && numplayers <= 4 )
	{
		m_numplayers = numplayers;
		//kasowanie starej tablicy jesli istnieje
		deleteArray();
		string name;
		for( int i = 0; i < m_numplayers; i++ )
		{
			name = "Gracz ";
			name += char(i + 49);

			switch( i )
			{
				case 0:
					//key map: up - arrow up  down - arrow down  left - arrow left  right - arrow right bomb - lshift  
					m_playersArray.push_back(new Player(1, 1, name, 0x26, 0x28, 0x25, 0x27, 0xA1));
					break;
				case 1:
					//key map: up - w  down - s  left - a  right - d bomb - q
					m_playersArray.push_back(new Player(sizex - 2, sizey - 2, name, 0x57, 0x53, 0x41, 0x44, 0x51));
					break;
				case 2:
					//key map: up - u  down - j  left - h  right - k bomb - y
					m_playersArray.push_back(new Player(1, sizey - 2, name, 0x55, 0x4A, 0x48, 0x4B, 0x59));
					break;
				case 3:
					//key map: up - NUM 8  down - NUM 5  left - NUM 4  right - NUM 6 bomb - NUM 7
					m_playersArray.push_back(new Player(sizex - 2, 1, name, 0x68, 0x65, 0x64, 0x66, 0x67));
					break;
			};
		}
		return true;
	}
	return false;
}

//rysuje gracza
void Players::draw()
{
	int i = 0;
	for(player_iter r = m_playersArray.begin(); r != m_playersArray.end(); r++ )
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN + i*i++);
		dynamic_cast<Player*>(*r)->draw();
	}
}

//rysuje status gracza
void Players::drawStatus(int x)
{
	int i = 0;
	for( player_iter r = m_playersArray.begin(); r != m_playersArray.end(); r++ )
	{
		COORD c;
		c.X = x + 5;
		c.Y = 2 + i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN + i*i++);

		dynamic_cast<Player*>(*r)->drawStatus(x);
	}
}

//ruch gracza
void Players::move(Player *p, DIRECTION dir, Field * f)
{
		//if 2 players are on the same position reset theirs draws
		for( player_iter r = m_playersArray.begin(); r != m_playersArray.end(); r++ )
		{
			Player* tmp = dynamic_cast<Player*>(*r);
			if( p != tmp )
			{
				if( *p == *tmp )
				{
					tmp->resetDraw();
				}
			}
		}
		
		Object* tmp_object = nullptr;
		switch( dir )
		{
			case UP:
				tmp_object = dynamic_cast<Object*>(f->getObj(p->getx(), p->gety() - 1));
				break;
			case DOWN:
				tmp_object = dynamic_cast<Object*>(f->getObj(p->getx(), p->gety() + 1));
				break;
			case LEFT:
				tmp_object = dynamic_cast<Object*>(f->getObj(p->getx() - 1, p->gety()));
				break;
			case RIGHT:
				tmp_object = dynamic_cast<Object*>(f->getObj(p->getx() + 1, p->gety()));
				break;
			case BOMB:
				//podloz bombe tylko jesli gracz stoi na EmptyObject i ma bomby
				if( dynamic_cast<EmptyObject*>(f->getObj(p->getx(), p->gety())) && p->plantBomb() )
				{
						f->putObject(new Bomb(p->getx(), p->gety(), p));
				}
				break;
			default:
				break;
		};
		//jesli w kierunku ruchu jest pusty obiekt to tam idz
		if( EmptyObject* tmp_empty = dynamic_cast<EmptyObject *>(tmp_object) )
		{
			f->getObj(p->getx(), p->gety())->resetDraw();
			//jesli tam gdzie poszedl gracz obiekt plonie to gracz ginie
			if( tmp_empty->isFire() )
				p->kill();
			//jesli nie to tam idzie
			else
				p->moveDir(dir);
		}
		//jesli w kierunku ruchu jest bonus to zabierz go i zastap go pustym obiektem
		else  if( Bonus* tmp_bonus = dynamic_cast<Bonus *>(tmp_object) )
		{
			switch( tmp_bonus->getBonus() )
			{
				case BOMB_POWER:
					p->getBonusBombPower();
					break;
				case BOMB_QUANITY:
					p->getBonusBombQuanity();
					break;
				default:
					break;
			}

			f->putObject(new EmptyObject(tmp_bonus->getx(), tmp_bonus->gety(), false));

			p->resetDrawStatus();
			f->getObj(p->getx(), p->gety())->resetDraw();
			p->moveDir(dir);
		}

}

//sprawdz akcje wszystkich graczy
void Players::getEvents(Field * f)
{
	for( player_iter p = m_playersArray.begin(); p != m_playersArray.end(); p++ )
	{
		Player* tmp_player = dynamic_cast<Player*>(*p);
		if( tmp_player->isAlive() )
		{
			DIRECTION dir = tmp_player->move();
			if( dir != NONE )
				move(tmp_player, dir, f);
		}
	}
}

//sprawdza kto wygral
int Players::checkWinner()
{
	int numberalive = 0, tmp = 0, alive = 0;
	for( player_iter r = m_playersArray.begin(); r != m_playersArray.end(); r++ )
	{
		tmp++;
		if( dynamic_cast<Player*>(*r)->isAlive() )
		{
			numberalive++;
			alive = tmp;
		}
	}
	if( numberalive <= 1 && numberalive != m_numplayers )
	{
		if( numberalive == 0 )
		{
			return 5;
		}
		else if( m_numplayers != 1 )
			return alive;
		else
			return 5;
	}
	else
		return 0;
}

//kasuje tablice graczy
bool Players::deleteArray()
{
	for(player_iter r = m_playersArray.begin(); r != m_playersArray.end(); r++ )
	{ 
		delete *r;
	}
	m_playersArray.clear();
	return true;
}

//destruktor
Players::~Players()
{
	deleteArray();
}
