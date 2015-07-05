#pragma once

enum DIRECTION {UP = 0, DOWN, LEFT, RIGHT, BOMB, NONE};

class Controller
{
private:
	//mapa przyciskow
	int m_up;
	int m_down;
	int m_left;
	int m_right;
	int m_bomb;
public:

	//konstruktor z argumentami (numery przyciskow)
	Controller(int up, int down, int left, int right, int bomb) : m_up(up), m_down(down), m_left(left), m_right(right), m_bomb(bomb) {}
	
	//ustawienie przyciskow
	void setKeys(int up, int down, int left, int right, int bomb);
	//zwroc wcisniety klawisz
	DIRECTION readInput();
	~Controller();
};

