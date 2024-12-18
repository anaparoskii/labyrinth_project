#include <iostream>
#include "Cell.h"
#include "Labyrinth.h"

Labyrinth::Labyrinth() {
	this->matrix = nullptr;
	this->rows = 0;
	this->cols = 0;
	this->itemNumber = 0;
}

Labyrinth::Labyrinth(unsigned int rows, unsigned int cols, int itemumber) {
	this->rows = rows;
	this->cols = cols;
	this->itemNumber = itemumber;
	this->matrix = this->generateLabyrinth();
}

Cell** Labyrinth::generateLabyrinth() {
	// inicijalizacija matrice
	this->matrix = new Cell * [rows];
	for (unsigned int i = 0; i < rows; i++) {
		this->matrix[i] = new Cell[cols];
		for (unsigned int j = 0; j < cols; j++) {
			// postavlja zidove na ivice matrice
			if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
				this->matrix[i][j] = Cell(i, j, '#');
			}
			// na ostala mesta postavlja prolaze
			else {
				this->matrix[i][j] = Cell(i, j, '.');
			}
		}
	}

	// postavljanje ulaza u prvi red matrice i postavljanje robota ispod ulaza
	int entrence = 1 + std::rand() % (cols - 2);
	this->matrix[0][entrence] = Cell(0, entrence, 'U');
	this->matrix[1][entrence] = Cell(1, entrence, 'R');

	// postavljanje izlaza u poslednji red matrice
	int exit = 1 + std::rand() % (cols - 2);
	this->matrix[rows - 1][exit] = Cell(rows - 1, exit, 'I');

	// postavljanje predmeta
	for (int i = 0; i < itemNumber; i++) {
		int randRow = 1 + std::rand() % (cols - 2);
		int randCol = 1 + std::rand() % (cols - 2);
		this->matrix[randRow][randCol] = Cell(randRow, randCol, 'P');
	}

	// postavljanje minotaura
	int randRow = 1 + std::rand() % (cols - 2);
	int randCol = 1 + std::rand() % (cols - 2);
	this->matrix[randRow][randCol] = Cell(randRow, randCol, 'M');

	// postavljanje ostalih zidova
	// broj zidova 2*(rows + cols)
	for (unsigned int i = 0; i < 2 * (rows + cols); i++) {
		int randRow = 1 + std::rand() % (cols - 2);
		int randCol = 1 + std::rand() % (cols - 2);
		if (this->matrix[randRow][randCol].getType() == '.') {
			this->matrix[randRow][randCol] = Cell(randRow, randCol, '#');
		}
	}

	return this->matrix;
}

Labyrinth::~Labyrinth() {
	for (unsigned int i = 0; i < rows; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

unsigned int Labyrinth::getRows() {
	return this->rows;
}

void Labyrinth::setRows(unsigned int rows) {
	this->rows = rows;
}

unsigned int Labyrinth::getCols() {
	return this->cols;
}

void Labyrinth::setCols(unsigned int cols) {
	this->cols = cols;
}

int Labyrinth::getItemNumber() {
	return this->itemNumber;
}

void Labyrinth::setItemNumber(int itemNumber) {
	this->itemNumber = itemNumber;
}

Cell** Labyrinth::getMatrix() {
	return this->matrix;
}

Cell* Labyrinth::operator[](unsigned int row) {
	return this->matrix[row];
}

void Labyrinth::showMatrix() {
	for (unsigned int i = 0; i < this->rows; i++) {
		for (unsigned int j = 0; j < this->cols; j++) {
			std::cout << this->matrix[i][j].getType();
		}
		std::cout << std::endl;
	}
}
