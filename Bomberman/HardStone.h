#pragma once
#include "Object.h"


class HardStone :
	public Object
{
private:
public:
	//domyslny konstruktor
	HardStone(int x = -1, int y = -1, char s = char(219) ) : Object(x, y, s) { }
	//rysowanie
	virtual void draw();
	~HardStone();
};

