#include "stdafx.h"
#include "HardStone.h"

//rysowanie
void HardStone::draw()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY-1);
	Object::draw();
}

HardStone::~HardStone()
{
}
