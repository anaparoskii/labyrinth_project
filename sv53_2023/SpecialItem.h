#pragma once
#include <iostream>
#include <string>
#include "Cell.h"

class SpecialItem : public Cell {
	/*
	Ova klasa nasledjuje klasu Cell
	Predstavlja specijalne predmete na tabli
	Ovoj klasi su dodati novi atributi itemName, active, movesLeft
	Dodato je i 4 nove funkcije koje predstavljaju 'moc' predmeta
	Autor: Ana Paroski
	Poslednja izmena: 05.01.2025.
	*/
private:
	std::string itemName;  // naziv predmeta
	bool active; // da li je predmet aktivan
	int movesLeft; // koliko je predmet jos poteza aktivan

public:
	// konstrukori i destruktor
	SpecialItem();
	SpecialItem(unsigned int x, unsigned int y, std::string itemName);
	~SpecialItem();

	// getter i setter za nove atribute
	std::string getItemName();
	void setItemName(std::string itemName);

	bool isActive();
	void setActive(bool active);

	int getMovesLeft();
	void setMovesLeft(int movesLeft);

	// funkcije za 4 moci predmeta
	SpecialItem& activateFogOfWar();
	SpecialItem& activateSword();
	SpecialItem& activateShield();
	SpecialItem& activateHammer();

	SpecialItem& operator=(const SpecialItem& otherItem);

};
