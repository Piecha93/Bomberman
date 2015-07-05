#include "stdafx.h"
#include "Bonus.h"

//losowanie bonusu (sila wybuchy lub wiecej bomb)
BONUS Bonus::getBonus()
{
	if( rand() % 2 )
		return BOMB_POWER;
	else
		return BOMB_QUANITY;
}

//rysowanie
void Bonus::draw()
{
	//ustawienie koloru konsoli
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x9);
	Object::draw();
}

Bonus::~Bonus()
{
}
