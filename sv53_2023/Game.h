#pragma once
#include <iostream>
#include "Cell.h"
#include "Labyrinth.h"
#include "SpecialItem.h"

class Game {
	/*
	Klasa koja omogucava tok igre
	Autor: Ana Paroski
	Poslednja izmena: 04.01.2025.
	*/
private:
	Labyrinth& labyrinth;  // lavirint
	bool play;  // da li je igra u toku
	bool won;  // da li je robot pobedio
	bool lost;  // da li je minotaur pobedio
	const char minotaurMoves[4] = { 'W', 'A', 'S', 'D' };  // konstanta koja se koristi pri biranju nasumicnog poteza minotaura

public:
	// konstruktori i destruktor
	Game(Labyrinth& labyrinth);
	Game(Labyrinth& labyrinth, bool play, bool won, bool lost);
	~Game();

	// getteri i setteri za sve atribute klase
	Labyrinth& getLabyrinth();
	void setLabyrinth(Labyrinth& labyrinth);

	bool isPlay();
	void setPlay(bool play);

	bool isWon();
	void setWon(bool won);

	bool isLost();
	void setLost(bool lost);

	// funkcija koja predstavlja tok igre
	void startGame();

	// pomocne funckije
	void updateActiveItems();
	void showMatrix();
	void wallCollision(int currentRobotX, int currentRobotY, int newRobotX, int newRobotY);
	void minotaurCollision(int currentRobotX, int currentRobotY, int newRobotX, int newRobotY);
	void itemCollection(int currentRobotX, int currentRobotY, int newRobotX, int newRobotY);
	bool robotCollision(int robotX, int robotY, int minotaurX, int minotaurY);
	bool robotMove(int newRobotX, int newRobotY);
	void handleEnd();

	/*
	Funkcije koje proveravaju da li su odredjeni specijalni predmeti aktivni
	Parametri: referenca na listu pokupljenih specijalnih predmeta i ukupan broj specijalnih predmeta na tabli
	Povratna vrednost: true ili false
	*/
	bool swordActive(SpecialItem* itemList, int length);
	bool hammerActive(SpecialItem* itemList, int length);
	bool shieldActive(SpecialItem* itemList, int length);
	bool fogActive(SpecialItem* itemList, int length);

};
