#pragma once

class Cell {
	/*
	Klasa koja predstavlja celiju matrice
	Autor: Ana Paroski
	Poslednja izmena: 18.12.2024. 
	*/
private:
	unsigned int x;  // x koordinata celije
	unsigned int y;  // y koordinata celije
	char type;       // tip celije (zid '#', prolaz '.', itd)

public:
	// konstruktori i destruktor
	Cell();
	Cell(unsigned int x, unsigned int y, char type);

	~Cell();

	// getteri i setteri za sve atribute klase
	unsigned int getX();
	void setX(unsigned int x);

	unsigned int getY();
	void setY(unsigned int y);

	char getType();
	void setType(char type);

	// preklopljen operator dodele =
	Cell& operator=(const Cell& otherCell);
	Cell& operator=(char newType);
};
