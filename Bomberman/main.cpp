// Bomberman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Bomberman.h"

int main()
{
	//dla liczb losowych
	srand((unsigned)time(0));

	Bomberman bomberman;
	bomberman.run();
	return 0;
}

