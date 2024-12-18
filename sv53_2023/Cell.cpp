#include <iostream>
#include "Cell.h"

Cell::Cell() {
	this->x = 0;
	this->y = 0;
	this->type = ' ';
}

Cell::Cell(unsigned int x, unsigned int y, char type) {
	this->x = x;
	this->y = y;
	this->type = type;
}
Cell::~Cell() {}

unsigned int Cell::getX() {
	return this->x;
}

void Cell::setX(unsigned int x) {
	this->x = x;
}

unsigned int Cell::getY() {
	return this->y;
}

void Cell::setY(unsigned int y) {
	this->y = y;
}

char Cell::getType() {
	return this->type;
}

void Cell::setType(char type) {
	if (type == '.' || type == '#' || type == 'I' || type == 'U' || type == 'R' || type == 'M' || type == 'P') {
		this->type = type;
	}
	throw std::invalid_argument("Invalid type argument!");
}

Cell& Cell::operator=(const Cell& otherCell) {
	if (this != &otherCell) {
		this->x = otherCell.x;
		this->y = otherCell.y;
		this->type = otherCell.type;
	}
	return *this;
}

Cell& Cell::operator=(char newType) {
	this->type = newType;
	return *this;
}
