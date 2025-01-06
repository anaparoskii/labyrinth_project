#include <iostream>
#include "Labyrinth.h"
#include "Game.h"

/*
Ovde se nalazi postavka igre - bira se dimenzija matrice i broj specijalnih predmeta na tabli
Autor: Ana Paroski
Poslednja izmena: 04.01.2025.
*/

const bool PLAY = true;
const bool WON = false;
const bool LOST = false;

int main() {
	std::cout << "~~~ KNOSSOS LABYRINTH ~~~" << std::endl;
	unsigned int rows;
	unsigned int cols;
	int itemNumber;
	// parametri se unose dok se ne unesu odgovarajuce vrednosti
	while (true) {
		std::cout << "Enter row number: " << std::endl;
		std::cin >> rows;
		if (rows >= 15) {
			break;
		}
		else {
			std::cout << "Number of rows must be 15 or bigger!" << std::endl;
		}
	}
	while (true) {
		std::cout << "Enter column number: " << std::endl;
		std::cin >> cols;
		if (cols >= 15) {
			break;
		}
		else {
			std::cout << "Number of columns must be 15 or bigger!" << std::endl;
		}
	}
	while (true) {
		std::cout << "Enter number of special items: " << std::endl;
		std::cin >> itemNumber;
		if (itemNumber >= 3) {
			break;
		}
		else {
			std::cout << "Number of special items must be 3 or bigger!" << std::endl;
		}
	}

	Labyrinth labyrinth(rows, cols, itemNumber);

	bool play = PLAY;
	bool won = WON;
	bool lost = LOST;

	Game game(labyrinth, play, won, lost);
	game.startGame();

	return 0;
}