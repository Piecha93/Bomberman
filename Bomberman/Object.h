#pragma once
class Object
{
private:
	//wspolrzedne obiektu
	int m_x;
	int m_y;
	//znak do rysowania
	char m_sign;
protected:
	//czy rysowac? (tak jesli zaszla jakas zmiana) Protected poniewaz czesto uzywana podczas przeladowac w klasach pochodnych
	bool m_draw;
public:
	//konstruktor domyslny
	Object(int x = -1, int y = -1, char s = 'x') : m_x(x), m_y(y), m_sign(s), m_draw(true) { }
	//konstruktor kopiujacy
	Object(Object & obj);
	//akcesory
	char getSign() const { return m_sign; }
	int getx() const { return m_x; }
	int gety() const { return m_y; }
	bool getDraw() { return m_draw; }
	//ustawienia znaku i wspolrzednych
	void setsign(char s) { m_sign = s; }
	void setx(int x) { m_x = x; }
	void sety(int y) { m_y = y; }
	void setxy(int x, int y){ setx(x); sety(y); }
	//resetuje rysowanie (uzywane przy jakichkolwiek zmianach)
	void resetDraw() { m_draw = true; }
	//zamiana wspolrzednych z innym obiektem
	void swapCoord(Object *obj);
	//uaktualnij
	virtual void update(int time) {};
	//rysuj
	virtual void draw();
	//porownanie wspolrzednych obiektow
	bool operator==(Object & p);
	//destruktor
	virtual ~Object();
};

