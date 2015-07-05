#include "stdafx.h"
#include "Menu.h"

//konstruktor
Menu::Menu()
{
	menuStart[0] = "Start gry";
	menuStart[1] = "Instrukcje";
	menuStart[2] = "Ustawienia";
	menuStart[3] = "Wyjscie";

	menuInstructions[0] = "Sterowanie: ";
	menuInstructions[1] = "Gracz 1   Ruch - strzalki Bomba - prawy shift";
	menuInstructions[2] = "Gracz 2   Ruch - wsad     Bomba - q";
	menuInstructions[3] = "Gracz 3   Ruch - ujhk     Bomba - y";
	menuInstructions[4] = "Gracz 4   Ruch - NUM 8546 Bomba - NUM 7";
	menuInstructions[5] = "";
	menuInstructions[6] = "Wcisnij enter aby wrocic";

}

//obsluga menu
MENU_STATUS Menu::drawMenu()
{
	MENU_STATUS choice = MAIN;

	while( choice != START_GAME )
	{
		Sleep(100);
		switch( choice )
		{
			case MAIN:
				choice = drawMain();
				break;
			case SETTINGS:
				choice = drawSettings();
				break;
			case INSTRUCTIONS:
				choice = drawInstructions();
				break;
			case EXIT:
				return EXIT;
				break;
			default:
				return EXIT;
				break;
		}	
	}
	return START_GAME;
}

//menu glowne
MENU_STATUS Menu::drawMain()
{
	//czyszczenie ekranu
	system("cls");
	m_position = 1;
	while( true )
	{
		for( int i = 0; i < 4; i++ )
		{
			COORD c;
			c.X = 25;
			c.Y = 5 + i;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			if( m_position == i )
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY + BACKGROUND_BLUE);
			else
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_INTENSITY - 1) | 0);
			cout << menuStart[i];
		}
	
		if( GetAsyncKeyState(VK_UP) )
		{
			if( m_position == 0 )
				m_position = 3;
			else
				m_position--;
		}
		else if( GetAsyncKeyState(VK_DOWN) )
		{
			if( m_position == 3 )
				m_position = 0;
			else
				m_position++;
		}
		else if( GetAsyncKeyState(VK_RETURN) )
		{
			switch( m_position )
			{
				case 0:
					return START_GAME;
					break;
				case 1:
					return INSTRUCTIONS;
					break;
				case 2:
					return SETTINGS;
					break;
				case 3:
					return EXIT;
					break;
				default:
					return EXIT;
					break;
			}
		}
		Sleep(100);
	}
	return EXIT;
} 

//instrukcje
MENU_STATUS Menu::drawInstructions()
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_INTENSITY - 1) | 0);
	for( int i = 0; i < 7; i++ )
	{
		COORD c;
		c.X = 25;
		c.Y = 5 + i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

		cout << menuInstructions[i];
	}
	
	while( true )
	{
		if( GetAsyncKeyState(VK_RETURN) )
			return MAIN;
	}
}

//ustawienia
MENU_STATUS Menu::drawSettings()
{
	system("cls");
	while( true )
	{
		if( GetAsyncKeyState(VK_RETURN) )
			return MAIN;
	}
}


Menu::~Menu()
{

}