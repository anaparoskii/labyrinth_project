#pragma once

class Cell {
private:
	unsigned int x;
	unsigned int y;
	char type;

public:
	Cell();
	Cell(unsigned int x, unsigned int y, char type);

	~Cell();

	unsigned int getX();
	void setX(unsigned int x);

	unsigned int getY();
	void setY(unsigned int y);

	char getType();
	void setType(char type);

	Cell& operator=(const Cell& otherCell);
	Cell& operator=(char newType);
};
