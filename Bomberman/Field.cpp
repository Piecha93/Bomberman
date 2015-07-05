#include "stdafx.h"
#include "Field.h"
#include "Object.h"
#include "EmptyObject.h"
#include "HardStone.h"
#include "Stone.h"
#include "Bomb.h"
#include "Bonus.h"
#include "Player.h"
#include <vector>

//generuje plansze 
bool Field::generator()
{
	//kasuje stara tablice jesli istnieje
	deleteArray();

	//ustawienie rozmiaru wektora recznie poniewaz jest 2D
	m_objArray.resize(m_sizex);
	for (int i = 0; i < m_sizex; i ++)
	{
		m_objArray[i].resize(m_sizey);
		for (int j = 0; j < m_sizey; j++)
		{
			//wstawiania HardStonow
			if (i == 0 || j == 0 || i == (m_sizex - 1) || j == (m_sizey - 1) || //obwodka
				!(i % 2) && !(j % 2))											//srodek
			{
				m_objArray[i][j] = new HardStone(i, j);
			}
			//czyszczenie katow dla graczy
			else if (	
					(	1 == j == i || i + j == 3 )	||													//kat gracza 1
					(	i == m_sizex - 2 && j == m_sizey - 2) || (i + j) == (m_sizex + m_sizey - 5) ||	//kat gracza 2
					(	i < 3 && j > m_sizey -4) 	||													//kat gracza 3
					(	i > m_sizex -4 && j < 3)														//kat gracza 4
					)														
			{
				m_objArray[i][j] = new EmptyObject(i, j);
			}
			else
			{
				//generowanie Stonow i pustych miejsc w stosunku 3:1
				if (rand() % 3)
					m_objArray[i][j] = new Stone(i, j);
				else
					m_objArray[i][j] = new EmptyObject(i, j);
			}
		}
	}
	return true;
}

//rysowania planszy
bool Field::draw()
{
	for( object_iter1 r = m_objArray.begin(); r != m_objArray.end(); r++ )
	{
		for( object_iter2 c = r->begin(); c != r->end(); c++ )
		{
			//rysuje tylko jesli uaktualniono
			dynamic_cast<Object*>(*c)->draw();
		}
	}
	return true;
}

//wloz obiekt na miejsce innego
bool Field::putObject(int x, int y, Object * obj)
{
	if( !m_objArray.empty() && x >= 1 && y >= 1 && x < m_sizex && y < m_sizey )
	{
		//kasuje stary objekt
		delete m_objArray[x][y];
		m_objArray[x].erase(m_objArray[x].begin() + y);
		//putting new object			
		m_objArray[x].insert(m_objArray[x].begin() + y, obj);
		m_objArray[x][y]->setxy(x, y);
		//set draw to true
		m_objArray[x][y]->resetDraw();
		return true;
	}
	return false;
}

//wloz obiekt na miejsce innego
bool Field::putObject(Object * obj)
{
	int x = obj->getx();
	int y = obj->gety();
	return putObject(x, y, obj);
}

//kasuje stara tablice jesli istnieje
bool Field::deleteArray()
{
	for( object_iter1 r = m_objArray.begin(); r != m_objArray.end(); r++ )
	{
		for( object_iter2 c = r->begin(); c != r->end(); c++ )
		{
			delete *c;
		}
	}
	m_objArray.clear();
	return true;
}

//wybuch bomby w odpowiednim kierunku
void Field::checkExplosion(Bomb* bomb, Players* pl, DIRECTION dir)
{
	//sprawdz w odleglosci sily wybuchu
	for( int i = 1; i <= bomb->getPower(); i++ )
	{
		Object* tmp_obj = nullptr;
		//sprawdzanie odpowiedniego kierunku i bobranie obiektu ktory stoi na drodze wybuchy
		switch( dir )
		{
			case RIGHT:
				tmp_obj = getObj(bomb->getx() + i, bomb->gety());
				break;
			case LEFT:
				tmp_obj = getObj(bomb->getx() - i, bomb->gety());
				break;
			case UP:
				tmp_obj = getObj(bomb->getx(), bomb->gety() - i);
				break;
			case DOWN:
				tmp_obj = getObj(bomb->getx(), bomb->gety() + i);
				break;
			default:
				tmp_obj = nullptr;
				break;
		};

		if( tmp_obj )
		{
			//jezeli w miescu wybuchu stoi gracz - ginie a wybuch leci dalej
			for( player_iter r = pl->getIteratorBegin(); r != pl->getIteratorEnd(); r++ )
			{
				Player* tmp_player = dynamic_cast<Player*>(*r);
				if( static_cast<Object>(*tmp_player) == *tmp_obj )
				{
					tmp_player->kill();
				}
			}
			//jestli natrafi na HardStone to konczy wybuch
			if( dynamic_cast<HardStone*>(tmp_obj) )
			{
				//wychodzi z petli
				break;
			}
			//jesli w miejscu wybuchu jest pusty obiekt podpala go i leci dalej
			else if( EmptyObject* tmp_empty = dynamic_cast<EmptyObject*>(tmp_obj) )
			{
				tmp_empty->setFire();
			}
			//jesli znajduje sie kamien to go niszczy, wstawia na to miejsce pusty element i losuje bonus (20% szans)
			else if( dynamic_cast<Stone*>(tmp_obj) )
			{
				if( rand() % 5 )
				{
					putObject(new EmptyObject(tmp_obj->getx(), tmp_obj->gety(), false));
				}
				else
				{
					putObject(new Bonus(tmp_obj->getx(), tmp_obj->gety()));
				}
				//break poniewaz natrafienie na Stone zatrzymuje eksplozje
				break;
			}
			//jesli w miejscu wybuchu jest bonus - niszczy go i wstawia pusty podlapoly element
			else if( dynamic_cast<Bonus*>(tmp_obj) )
			{
				putObject(new EmptyObject(tmp_obj->getx(), tmp_obj->gety(), true));
			}
			//jesli w miescu wybuchu stoi inna bomba - skraca czas jej wybuchy o 2,5 sekundy
			else if( Bomb *tmp_bomb = dynamic_cast<Bomb*>(tmp_obj) )
			{
				tmp_bomb->update(2500);
			}
		}
	}
}

//uaktualnij mape (bomby, plonace obiekty, kolizje itp)
void Field::update(int time, Players* pl)
{
	for( object_iter1 r = m_objArray.begin(); r != m_objArray.end(); r++ )
	{
		for( object_iter2 c = r->begin(); c != r->end(); c++ )
		{
			//uaktualnienie obiektu
			dynamic_cast<Object*>(*c)->update(time);
			//jesli obiekt jest bomba
			if( Bomb* tmp_bomb = dynamic_cast<Bomb*>(*c) )
			{
				//jesli eksplodowala
				if( tmp_bomb->getBangStatus() )
				{
					//sprawdz prawo
					checkExplosion(tmp_bomb, pl, RIGHT);
					//sprawdz lewo
					checkExplosion(tmp_bomb, pl, LEFT);
					//sprawdz dol
					checkExplosion(tmp_bomb, pl, DOWN);
					//sprawdz gore
					checkExplosion(tmp_bomb, pl, UP);
					
					//jesli gracz "siedzi" na bombie
					for( player_iter r = pl->getIteratorBegin(); r != pl->getIteratorEnd(); r++ )
					{
						Player* tmp_player = dynamic_cast<Player*>(*r);
						if( static_cast<Object>(*tmp_player) == static_cast<Object>(*tmp_bomb) )
						{
							tmp_player->kill();
						}
					}
					//na konciec w miejsce wybuchy wklada pusty obiekt
					putObject( new EmptyObject(tmp_bomb->getx(), tmp_bomb->gety(), true) );
					c = r->begin();
				}
			}
		}
	}
}

//destruktor
Field::~Field()
{
	deleteArray();
}