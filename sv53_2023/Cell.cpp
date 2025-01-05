#include <iostream>
#include "Cell.h"

/* 
Ovaj modul sadrzi funkcije koje rade sa celijom matrice
Autor: Ana Paroski
Poslednja izmena: 18.12.2024.
*/

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
	this->type = type;
}

Cell& Cell::operator=(const Cell& otherCell) {
	/*
	preklopljen operator dodele koji izjednacava celiju sa drugom celijom
	parametri: referenca na dodeljenu celiju
	povratna vrednost: referenca na izmenjenu celiju
	*/
	if (this != &otherCell) {
		this->x = otherCell.x;
		this->y = otherCell.y;
		this->type = otherCell.type;
	}
	return *this;
}

Cell& Cell::operator=(char newType) {
	/*
	preklopljen operator dodele koji dodeljuje tip celiji
	parametri: tip koji se dodeljuje
	povratna vrednost: referenca na izmenjenu celiju
	*/
	this->type = newType;
	return *this;
}
