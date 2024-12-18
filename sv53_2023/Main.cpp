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

	Labyrinth l(rows, cols, itemNumber);
	l.showMatrix();
	return 0;
}