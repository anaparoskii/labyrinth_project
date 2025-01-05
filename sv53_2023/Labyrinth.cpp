#include <iostream>
#include "Cell.h"
#include "Labyrinth.h"
#include "GenerateLabyrinth.h"

/*
Modul koji sadrzi funkcije za rad sa lavirintom
Autor: Ana Paroski
Poslednja izmena: 04.01.2025.
*/

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
	/*
	preklopljen opetator [] pristupa redu matrice
	parametri: broj reda matrice
	povratna vrednost: red matrice
	*/
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
