#pragma once
#include "Players.h"
#include "Object.h"
#include <vector>

//deklaracje zapowadajace
class Object;
class Players;
class Bomb;

//typedef dla iteratorow
typedef std::vector<std::vector<Object*> >::iterator object_iter1;
typedef std::vector<Object*>::iterator object_iter2;


class Field
{
private:
	//rozmiar mapy x,y (min - 7 max - 37, tylko nieparzyste)
	int m_sizex;
	int m_sizey;
	//vektor 2D przechowujacy tablice wskaznikow na obiekty
	std::vector< vector<Object*> > m_objArray;
public:
	//domyslny konstruktor
	Field(int x = 21, int y = 21) : m_sizex(x), m_sizey(y) { }
	//generuje plansze
	bool generator();
	//akcesory
	int getSizex() { return m_sizex; }
	int getSizey() { return m_sizey; }
	//rysuj potrzebne elementy
	bool draw();
	// rysuj calosc
	bool draw2();
	//wloz obiekt na miejsce innego
	bool putObject(int x, int y, Object * obj);
	//wloz obiekt na miejsce innego
	bool putObject(Object * obj);
	//wybuch bomby w odpowiednim kierunku
	void checkExplosion(Bomb* bomb, Players* pl, DIRECTION dir);
	//uaktualnij mape (bomby, plonace obiekty, kolizje itp)
	void update(int time, Players* pl);
	//uwalnia pamiec z tablicy obiektow m_objArray
	bool deleteArray();
	//akcesory
	Object* getObj(int x, int y) { return m_objArray[x][y]; }

	~Field();
};

