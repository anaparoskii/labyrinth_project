#include <iostream>
#include "Cell.h"
#include "Labyrinth.h"
#include "GenerateLabyrinth.h"

/*
Modul koji sadrzi funkcije za rad sa lavirintom
Autor: Ana Paroski
Poslednja izmena: 05.01.2025.
*/

Labyrinth::Labyrinth() 
: matrix(nullptr), rows(0), cols(0), itemNumber(0), itemList(nullptr) {
	this->robotCoordinates[0] = -1;
	this->robotCoordinates[1] = -1;
	this->minotaurCoordinates[0] = -1;
	this->minotaurCoordinates[1] = -1;
}

Labyrinth::Labyrinth(unsigned int rows, unsigned int cols, int itemNumber)
: rows(rows), cols(cols), itemNumber(itemNumber) {
	this->itemList = new SpecialItem[itemNumber];
	for (int i = 0; i < itemNumber; ++i) {
		itemList[i] = SpecialItem(-1, -1, "");
	}
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
	delete[] itemList;
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

SpecialItem* Labyrinth::getItemList() {
	return this->itemList;
}

void Labyrinth::setItemList(SpecialItem* itemList) {
	this->itemList = itemList;
}

Cell* Labyrinth::operator[](unsigned int row) {
	/*
	Preklopljen opetator [] pristupa redu matrice
	Parametri: broj reda matrice
	Povratna vrednost: red matrice
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
	std::cout << std::endl;
	printItems();
}

void Labyrinth::showFogMatrix() {
	std::cout << "...fog covered the field..." << std::endl;
	int robotX = robotCoordinates[0];
	int robotY = robotCoordinates[1];
	for (unsigned int i = robotX - 1; i < robotX + 2; i++) {
		for (unsigned int j = robotY - 1; j < robotY + 2; j++) {
			std::cout << this->matrix[i][j].getType();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	printItems();
}

void Labyrinth::printItems() {
	// ispis svih aktivnih predmeta
	for (int i = 0; i < this->itemNumber; i++) {
		if (itemList[i].isActive()) {
			std::cout << itemList[i].getItemName() << " - moves left: " << itemList[i].getMovesLeft() << std::endl;
		}
	}
}
