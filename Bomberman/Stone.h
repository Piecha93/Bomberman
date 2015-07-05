#pragma once
#include "Object.h"
class Stone :
	public Object
{
public:
	//domyslny konstruktor
	Stone(int x = -1, int y = -1, char s = char(177) ) : Object(x, y, s) { }
	//destruktor
	~Stone();
};

