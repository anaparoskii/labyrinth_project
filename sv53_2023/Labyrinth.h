#pragma once
#include "Cell.h"

class Labyrinth {
private:
	Cell** matrix;
	unsigned int rows;
	unsigned int cols;
	int itemNumber;
	int robotCoordinates[2];
	int minotaurCoordinates[2];

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

	int* getRobotCoordinates();
	void setRobotCoordinates(int row, int col);

	int* getMinotaurCoordinates();
	void setMinotaurCoordinates(int row, int col);

	Cell** getMatrix();

	Cell* operator[](unsigned int row);

	void showMatrix();

	/*Cell** generateLabyrinth();
	Cell** findPath();*/
};
