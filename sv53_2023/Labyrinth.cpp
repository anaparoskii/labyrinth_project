#include <iostream>
#include "Cell.h"
#include "Labyrinth.h"
#include "GenerateLabyrinth.h"

Labyrinth::Labyrinth() {
	this->matrix = nullptr;
	this->rows = 0;
	this->cols = 0;
	this->itemNumber = 0;
	this->robotCoordinates[0] = -1;
	this->robotCoordinates[1] = -1;
	this->minotaurCoordinates[0] = -1;
	this->minotaurCoordinates[1] = -1;
}

Labyrinth::Labyrinth(unsigned int rows, unsigned int cols, int itemumber) {
	this->rows = rows;
	this->cols = cols;
	this->itemNumber = itemumber;
	this->robotCoordinates[0] = -1;
	this->robotCoordinates[1] = -1;
	this->minotaurCoordinates[0] = -1;
	this->minotaurCoordinates[1] = -1;
	this->matrix = generateLabyrinth(*this);
}

//Cell** Labyrinth::findPath() {
//	int pathLength = 0;
//	// nalazi put od ulaza do izlaza tako sto random bira sledecu poziciju (levo [0], dole [1], desno [2])
//	unsigned int newRow = this->getRobotCoordinates()[0];
//	unsigned int newCol = this->getRobotCoordinates()[1];
//	// dok ne dodjemo do poslednjeg reda
//	while (newRow <= this->getRows()) {
//		int move = std::rand() % 3;
//		switch (move) {
//		case 0: {
//			newCol--;
//			break;
//		}
//		case 1: {
//			newRow++;
//			break;
//		}
//		case 2: {
//			newCol++;
//			break;
//		}
//		}
//
//		if (newRow > 0 && newRow < this->getRows() - 1 && newCol > 0 && newCol < this->getCols() - 1) {
//			// privremeno siguran put obelezavam zvezdicom
//			this->matrix[newRow][newCol] = Cell(newRow, newCol, '*');
//			pathLength++;
//		}
//		else if (newRow == this->getRows() - 1) {
//			this->matrix[newRow][newCol] = Cell(newRow, newCol, 'I');
//			break;
//		}
//		else {
//			// opcija van opsega, vracamo na pocetnu situaciju
//			switch (move) {
//			case 0: {
//				newCol++;
//				break;
//			}
//			case 1: {
//				newRow--;
//				break;
//			}
//			case 2: {
//				newCol--;
//				break;
//			}
//			}
//		}
//	}
//
//	// ukupan broj celija
//	int cellNumber = this->getRows() * this->getCols();
//	// oduzima se broj spoljasnjih zidova
//	cellNumber = cellNumber - 2 * (this->getRows() + this->getCols()) + 4;
//	// oduzima se minimalan broj unutrasnjih zidova
//	cellNumber = cellNumber - 2 * (this->getRows() + this->getCols());
//	// oduzima se duzina sigurnog puta
//	cellNumber = cellNumber - pathLength;
//	// polovina preostalih celija ce biti put, a druga polovina zidovi
//	for (unsigned int i = 0; i < cellNumber / 2; i++) {
//		while (true) {
//			int randRow = 1 + std::rand() % (cols - 2);
//			int randCol = 1 + std::rand() % (cols - 2);
//			if (this->matrix[randRow][randCol].getType() == '#') {
//				this->matrix[randRow][randCol] = Cell(randRow, randCol, '.');
//				break;
//			}
//		}
//	}
//
//	return this->matrix;
//}
//
//Cell** Labyrinth::generateLabyrinth() {
//	// inicijalizacija matrice
//	this->matrix = new Cell * [rows];
//	for (unsigned int i = 0; i < rows; i++) {
//		this->matrix[i] = new Cell[cols];
//		for (unsigned int j = 0; j < cols; j++) {
//			// postavlja samo zidove u matricu
//			this->matrix[i][j] = Cell(i, j, '#');
//		}
//	}
//
//	// postavljanje ulaza u prvi red matrice i postavljanje robota ispod ulaza
//	int entrence = 1 + std::rand() % (cols - 2);
//	this->matrix[0][entrence] = Cell(0, entrence, 'U');
//	this->matrix[1][entrence] = Cell(1, entrence, 'R');
//	this->robotCoordinates[0] = 1;
//	this->robotCoordinates[1] = entrence;
//
//	this->matrix = this->findPath();
//
//	// postavljanje predmeta
//	for (int i = 0; i < itemNumber; i++) {
//		while (true) {
//			int randRow = 1 + std::rand() % (cols - 2);
//			int randCol = 1 + std::rand() % (cols - 2);
//			if (this->matrix[randRow][randCol].getType() == '*' || this->matrix[randRow][randCol].getType() == '.') {
//				this->matrix[randRow][randCol] = Cell(randRow, randCol, 'P');
//				break;
//			}
//		}
//	}
//
//	// postavljanje minotaura
//	while (true) {
//		int randRow = 1 + std::rand() % (cols - 2);
//		int randCol = 1 + std::rand() % (cols - 2);
//		if (this->matrix[randRow][randCol].getType() == '*') {
//			this->matrix[randRow][randCol] = Cell(randRow, randCol, 'M');
//			this->setMinotaurCoordinates(randRow, randCol);
//			break;
//		}
//	}
//
//	// svaka '*' postaje '.'
//	for (unsigned int i = 0; i < this->getRows(); i++) {
//		for (unsigned int j = 0; j < this->getCols(); j++) {
//			if (this->matrix[i][j].getType() == '*') {
//				this->matrix[i][j] = '.';
//			}
//		}
//	}
//
//	return this->matrix;
//}

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

int* Labyrinth::getRobotCoordinates() {
	return this->robotCoordinates;
}

void Labyrinth::setRobotCoordinates(int row, int col) {
	this->robotCoordinates[0] = row;
	this->robotCoordinates[1] = col;
}

int* Labyrinth::getMinotaurCoordinates() {
	return this->minotaurCoordinates;
}

void Labyrinth::setMinotaurCoordinates(int row, int col) {
	this->minotaurCoordinates[0] = row;
	this->minotaurCoordinates[1] = col;
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
