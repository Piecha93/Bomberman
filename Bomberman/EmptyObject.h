#pragma once
#include "Object.h"
class EmptyObject :
	public Object
{
private:
	//czy plonie
	bool m_burn;
	//czas do zgasniecia
	int m_timeToBurn;
	//stala - domyslny czas ploniecia
	enum { BURNTIME = 1000 };
public:
	//domyslny konstruktor
	EmptyObject(int x = -1, int y = -1) : Object(x, y, ' '), m_burn(false) {}
	//konstruktor z argumentami
	EmptyObject(int x, int y, bool burn) : Object(x, y, ' '), m_burn(burn), m_timeToBurn(BURNTIME) {}
	//rysowanie
	virtual void draw();
	//uaktualnij czas ploniecia
	virtual void update(int time);
	//zapal
	void setFire();
	//akcesory
	bool isFire() { return m_burn; }
	~EmptyObject();
};

