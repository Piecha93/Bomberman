#include "stdafx.h"
#include "Bomberman.h"
#include "Game.h"
#include "Menu.h"

//uruchomienie programu
void Bomberman::run()
{
	m_menu = new Menu;
	//glowna petla programu
	while( true )
	{
		//uruchomienie menu
		if( m_menu->drawMenu() == START_GAME )
		{
			clock_t start, stop;
			m_game = new Game;
			m_game->initGame();
			//roznica czasu
			int diff = 0;
			//glowna petla gry
			while( !(m_game->checkWinner()) )
			{
				start = clock();
				m_game->getInput();
				m_game->update(diff);
				m_game->draw();
				Sleep(100);
				stop = clock();
				diff = stop - start;
			//	cout << "diff: " << diff<< endl;
			}
			delete m_game;
			m_game = nullptr;
		}
		else
		{
			break;
		}
	}
	return;
}

Bomberman::~Bomberman()
{
	if( m_game )
	{
		delete m_game;
		m_game = nullptr;
	}
	if( m_menu )
	{
		delete m_menu;
		m_game = nullptr;
	}
	m_game = nullptr;
	m_menu = nullptr;
}
