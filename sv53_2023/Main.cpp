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
	bool lost = false;
	char minotaurMoves[4] = {'W', 'A', 'S', 'D'};

	while (play) {
		labyrinth.showMatrix();
		char move;
		std::cout << "Make a move [W, A, S, D; Q - quit]: " << std::endl;
		std::cin >> move;
		bool moved = false;

		unsigned int newRow = labyrinth.getRobotCoordinates()[0];
		unsigned int newCol = labyrinth.getRobotCoordinates()[1];
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
			std::cout << "Quitting the game!" << std::endl;
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
				labyrinth.getMatrix()[labyrinth.getRobotCoordinates()[0]][labyrinth.getRobotCoordinates()[1]] = '.';
				if (labyrinth.getMatrix()[newRow][newCol].getType() == 'I') {
					won = true;
					play = false;
				}
				labyrinth.getMatrix()[newRow][newCol] = 'R';
				labyrinth.setRobotCoordinates(newRow, newCol);
			}
			moved = true;
		}
		if (!play) break;
		if (moved) {
			// logika za pomeranje minotaura 'M'
			bool minotaurMoved = false;
			int mRow = labyrinth.getMinotaurCoordinates()[0];
			int mCol = labyrinth.getMinotaurCoordinates()[1];
			int rRow = labyrinth.getRobotCoordinates()[0];
			int rCol = labyrinth.getRobotCoordinates()[1];
			// ako je pored minotaura robot, nek ga pojede
			if ((mRow == rRow && (mCol + 1 == rCol || mCol - 1 == rCol)) || (mCol == rCol && (mRow + 1 == rRow || mRow - 1 == rRow))) {
				labyrinth.getMatrix()[rRow][rCol] = 'M';
				labyrinth.getMatrix()[mRow][mCol] = '.';
				labyrinth.setMinotaurCoordinates(rRow, rCol);
				labyrinth.setRobotCoordinates(-1, -1);
				minotaurMoved = true;
				lost = true;
				play = false;
			}
			// ako nije
			while (!minotaurMoved) {
				int minotaurMove = std::rand() % 4;  // 4 moguca poteza - A, W, S, D
				char move = minotaurMoves[minotaurMove];
				unsigned int newRow = mRow;
				unsigned int newCol = mCol;
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
				if (newRow > 0 && newRow < labyrinth.getRows() - 1 && newCol > 0 && newCol < labyrinth.getCols() - 1) {
					if (labyrinth.getMatrix()[newRow][newCol].getType() != '#'
						&& labyrinth.getMatrix()[newRow][newCol].getType() != 'I'
						&& labyrinth.getMatrix()[newRow][newCol].getType() != 'U') {
						// logika za kupljenje predmeta 'P'
						// minotaur samo unisti predmet tako da nema potrebe za dodatnom logikom
						labyrinth.getMatrix()[mRow][mCol] = '.';
						if (labyrinth.getMatrix()[newRow][newCol].getType() == 'P') {
							std::cout << "Minotaur destroyed an object!" << std::endl;
						}
						labyrinth.getMatrix()[newRow][newCol] = 'M';
						labyrinth.setMinotaurCoordinates(newRow, newCol);
						minotaurMoved = true;
					}
				}
				if (minotaurMoved) break;
			}
		}
	}
	if (won) {
		labyrinth.showMatrix();
		std::cout << "You got out!!!" << std::endl;
	}
	else if (lost) {
		labyrinth.showMatrix();
		std::cout << "Minotaur caught you! :(" << std::endl;
	}
	return 0;
}