#pragma once
#include "Object.h"

enum BONUS { BOMB_POWER, BOMB_QUANITY};
class Bonus :
	public Object
{
public:
	//domyslny konstruktor
	Bonus(int x = -1, int y = -1, char s = '@') : Object(x, y, s) {}
	//akcesory
	BONUS getBonus();
	//rysuj
	virtual void draw();
	~Bonus();
};

