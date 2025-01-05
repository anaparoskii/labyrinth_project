#pragma once
#include <iostream>
#include "Cell.h"
#include "Labyrinth.h"

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

};
