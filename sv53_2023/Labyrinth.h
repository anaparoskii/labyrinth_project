#pragma once
#include "Cell.h"

class Labyrinth {
private:
	Cell** matrix;
	unsigned int rows;
	unsigned int cols;
	int itemNumber;

public:
	Labyrinth();
	Labyrinth(unsigned int rows, unsigned int cols, int itemNumber);
	~Labyrinth();

	unsigned int getRows();
	void setRows(unsigned int rows);

	unsigned int getCols();
	void setCols(unsigned int cols);

	int getItemNumber();
	void setItemNumber(int itemNumber);

	Cell** getMatrix();

	Cell* operator[](unsigned int row);

	void showMatrix();

	Cell** generateLabyrinth();
};
