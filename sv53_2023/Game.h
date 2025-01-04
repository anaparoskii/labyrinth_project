#pragma once
#include <iostream>
#include "Cell.h"
#include "Labyrinth.h"

class Game {
private:
	Labyrinth& labyrinth;
	bool play;
	bool won;
	bool lost;
	const char minotaurMoves[4] = { 'W', 'A', 'S', 'D' };

public:
	Game(Labyrinth& labyrinth);
	Game(Labyrinth& labyrinth, bool play, bool won, bool lost);
	~Game();

	Labyrinth& getLabyrinth();
	void setLabyrinth(Labyrinth& labyrinth);

	bool isPlay();
	void setPlay(bool play);

	bool isWon();
	void setWon(bool won);

	bool isLost();
	void setLost(bool lost);

	void startGame();

};
