#include "stdafx.h"
#include "Game.h"
#include "Field.h"


//inicjalizacja gry (tworzenie graczy i mapy)
bool Game::initGame()
{
	//domyslne ustawienia
	return initGame(SIZEX, SIZEY, NUMPLAYERS);
}

bool Game::initGame(int numplayers)
{
	//domyslne ustawienia
	return initGame(SIZEX, SIZEY, numplayers);
}

bool Game::initGame(int x, int y, int numplayers)
{
	system("cls");
	cout << "sizex: ";
	cin >> x;
	cout << "sizey: ";
	cin >> y;
	cout << "liczba graczy: ";
	cin >> numplayers;
	cin.clear();
	system("cls");
	resetGame();
	if( x % 2 == 0 )
		x++;
	if( x < 7 )
		x = 7;
	if( x > 39 )
		x = 39;
	
	if( y % 2 == 0 )
		y++;
	if( y < 7 )
		y = 7;
	if( y > 39 )
		y = 39;

	if( numplayers > 4 )
		numplayers = 4;
	if( numplayers < 1 )
		numplayers = 1;


	if( !(m_field = new Field(x, y)) )
		return m_initialized = false;

	if( !m_field->generator() )
		return m_initialized = false;
	
	if( !(m_players = new Players(numplayers, m_field->getSizex(), m_field->getSizey())) )
	   return m_initialized = false;

	return m_initialized = true;
}

//resetuje ustawienia do wartosci domyclnych
void Game::resetGame()
{
	if( m_field )
	{
		delete m_field;
		m_field = nullptr;
	}
	if( m_players )
	{
		delete m_players;
		m_players = nullptr;
	}
	m_initialized = false;
}


//pobierz akcje graczy
void Game::getInput()
{
	m_players->getEvents(m_field);
}

//uaktualnij plansze
void Game::update(int time)
{
	m_field->update(time, m_players);
}

//sprawdz kto wygral
bool Game::checkWinner()
{
	int winner = m_players->checkWinner();
	if( winner != 0 )
	{
		system("CLS");
		COORD c;
		c.X = 25;
		c.Y = 5;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		if( winner == 5 )
			cout << "NIKT NIE WYGRAL";
		else
			cout << "WYGRYWA GRACZ " << winner;
		c.X = 25;
		c.Y = 7;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		cout << "WCISNIJ ENTERBY KONTYNUOWAC";
		while( cin.get() == '\n' )
			continue;
		while( true )
		{
			if( GetAsyncKeyState(VK_RETURN) )
				break;
		}
		return true;
	}
	return false;
}
//rysuj plansze i graczy i status graczy
void Game::draw()
{
	//jesli poprawnie zainicjalizowano gre
	if( m_initialized )
	{
		m_field->draw();
		m_players->draw();
		m_players->drawStatus(m_field->getSizex());
	}
	else
	{
		system("CLS");
		cout << "BLAD! NIE UDALO SIE ZAINICJALIZOWAC GRY";
	}
}

//destruktor
Game::~Game()
{
	if( m_field )
	{
		delete m_field;
		m_field = nullptr;
	}
	if( m_players )
	{
		delete m_players;
		m_players = nullptr;
	}
}
