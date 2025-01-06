#include <iostream>
#include <string>
#include "SpecialItem.h"
#include "Cell.h"

/*
Ovaj modul sadrzi funkcije koje rade sa specijalnih predmetima
Autor: Ana Paroski
Poslednja izmena: 05.01.2025.
*/

SpecialItem::SpecialItem() 
	: Cell(0, 0, 'P'), itemName(""), active(false), movesLeft(0) {}

SpecialItem::SpecialItem(unsigned int x, unsigned int y, std::string itemName) 
	: Cell(x, y, 'P'), itemName(itemName), active(false), movesLeft(4) {}

SpecialItem::~SpecialItem() {}

std::string SpecialItem::getItemName() {
	return this->itemName;
}
void SpecialItem::setItemName(std::string itemName) {
	this->itemName = itemName;
}

bool SpecialItem::isActive() {
	return this->active;
}
void SpecialItem::setActive(bool active) {
	this->active = active;
}

int SpecialItem::getMovesLeft() {
	return this->movesLeft;
}
void SpecialItem::setMovesLeft(int movesLeft) {
	this->movesLeft = movesLeft;
}

SpecialItem& SpecialItem::activateFogOfWar() {
	/*
	Ova funkcija se odnosi na predmet 'magla rata'
	Magla rata smanjuje vidljivost robotu na 3x3
	*/
	this->active = true;
	this->itemName = "fog of war";
	return *this;
}

SpecialItem& SpecialItem::activateSword() {
	/*
	Ova funkcija se odnosi na predmet 'mac'
	Mac omogucava robotu da ubije minotaura
	*/
	this->active = true;
	this->itemName = "sword";
	return *this;
}

SpecialItem& SpecialItem::activateShield() {
	/*
	Ova funkcija se odnosi na predmet 'stit'
	Stit omogucava robotu da se zastiti od napada minotaura
	*/
	this->active = true;
	this->itemName = "shield";
	return *this;
}

SpecialItem& SpecialItem::activateHammer() {
	/*
	Ova funkcija se odnosi na predmet 'cekic'
	Cekic omogucava robotu da prodje kroz zidove
	*/
	this->active = true;
	this->itemName = "hammer";
	return *this;
}

SpecialItem& SpecialItem::operator=(const SpecialItem& otherItem) {
	if (this != &otherItem) {
		Cell::operator=(otherItem);
		itemName = otherItem.itemName;
		active = otherItem.active;
		movesLeft = otherItem.movesLeft;
	}
	return *this;
}