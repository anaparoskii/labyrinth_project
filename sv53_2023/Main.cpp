#include <iostream>
#include "Cell.h"
#include "Labyrinth.h"

int main() {
	std::cout << "~~~ KNOSSOS LABYRINTH ~~~" << std::endl;
	unsigned int rows;
	unsigned int cols;
	int itemNumber;
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

	bool play = true;
	bool won = false;
	char minotaurMoves[4] = {'W', 'A', 'S', 'D'};

	while (play) {
		labyrinth.showMatrix();
		char move;
		std::cout << "Make a move [W, A, S, D; Q - quit]: " << std::endl;
		std::cin >> move;
		bool moved = false;
		for (unsigned int i = 0; i < labyrinth.getRows(); i++) {
			for (unsigned int j = 0; j < labyrinth.getCols(); j++) {
				if (labyrinth.getMatrix()[i][j].getType() == 'R') {
					unsigned int newRow = i;
					unsigned int newCol = j;
					switch (move) {
						case 'W': case 'w': {
							newRow--;
							break;
						}
						case 'A': case 'a': {
							newCol--;
							break;
						}
						case 'S': case 's': {
							newRow++;
							break;
						}
						case 'D': case 'd': {
							newCol++;
							break;
						}
						case 'Q': case 'q': {
							std::cout << "Quitting the game!" << std::endl,
							play = false;
							break;
						}
						default: {
							std::cout << "Invalid move chosen!" << std::endl;
							moved = true;
							break;
						}
					}
					if (!play) break;
					if (!moved && newRow >= 0 && newRow < labyrinth.getRows() && newCol >= 0 && newCol < labyrinth.getCols()) {
						if (labyrinth.getMatrix()[newRow][newCol].getType() == '#') {
							std::cout << "You can't walk through walls..." << std::endl;
						}
						else {
							// logika za kupljenje predmeta 'P'
							labyrinth.getMatrix()[i][j] = '.';
							if (labyrinth.getMatrix()[newRow][newCol].getType() == 'I') {
								won = true;
								play = false;
							}
							labyrinth.getMatrix()[newRow][newCol] = 'R';
						}
						moved = true;
					}
				}
				if (!play) break;
			}
			if (!play) break;
		}
		if (moved) {
			// logika za pomeranje minotaura 'M'
			bool minotaurMoved = false;
			for (unsigned int i = 0; i < labyrinth.getRows(); i++) {
				for (unsigned int j = 0; j < labyrinth.getCols(); j++) {
					if (labyrinth.getMatrix()[i][j].getType() == 'M') {
						while (!minotaurMoved) {
							// ako je pored minotaura robot 'R' nek ga pojede
							int minotaurMove = std::rand() % 4;  // 4 moguca poteza - A, W, S, D
							char move = minotaurMoves[minotaurMove];
							unsigned int newRow = i;
							unsigned int newCol = j;
							switch (move) {
							case 'W': {
								newRow--;
								break;
							}
							case 'A': {
								newCol--;
								break;
							}
							case 'S': {
								newRow++;
								break;
							}
							case 'D': {
								newCol++;
								break;
							}
							}
							if (newRow >= 0 && newRow < labyrinth.getRows() && newCol >= 0 && newCol < labyrinth.getCols()) {
								if (labyrinth.getMatrix()[newRow][newCol].getType() != '#' 
									&& labyrinth.getMatrix()[newRow][newCol].getType() != 'I' 
									&& labyrinth.getMatrix()[newRow][newCol].getType() != 'U') {
									// logika za kupljenje predmeta 'P'
									labyrinth.getMatrix()[i][j] = '.';
									labyrinth.getMatrix()[newRow][newCol] = 'M';
									minotaurMoved = true;
								}
							}
						}
					}
				}
			}
		}
		if (won) {
			std::cout << "You got out!!!" << std::endl;
		}
	}
	return 0;
}