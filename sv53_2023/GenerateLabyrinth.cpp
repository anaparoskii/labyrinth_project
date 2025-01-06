#include <iostream>
#include <chrono>
#include "GenerateLabyrinth.h"
#include "Cell.h"
#include "Labyrinth.h"
#include "SpecialItem.h"

/*
Modul koji sadrzi definicije funkcija koje generisu lavirint
Autor: Ana Paroski
Poslednja izmena: 04.01.2025.
*/

Cell** generateLabyrinth(Labyrinth& labyrinth) {
	/*
	Ova funkcija generise lavirint, postavlja ulaz, robota, minotaura, predmete
	Takodje, meri vreme potrebno za generisanje lavirinta i ispisuje ga u mikrosekundama
	Parametri: referenca na lavirint koji se generise
	Povratna vrednost: matrica tog lavirinta
	*/

	auto start = std::chrono::high_resolution_clock::now();  // uzima trenutno vreme radi racunanja vremena potrebnog za generisanje

	// inicijalizacija matrice
	Cell** matrix;
	matrix = new Cell * [labyrinth.getRows()];
	for (unsigned int i = 0; i < labyrinth.getRows(); i++) {
		matrix[i] = new Cell[labyrinth.getCols()];
		for (unsigned int j = 0; j < labyrinth.getCols(); j++) {
			// postavlja samo zidove u matricu
			matrix[i][j] = Cell(i, j, '#');
		}
	}

	// postavljanje ulaza u prvi red matrice i postavljanje robota ispod ulaza
	int entrence = 1 + std::rand() % (labyrinth.getCols() - 2);
	matrix[0][entrence] = Cell(0, entrence, 'U');
	matrix[1][entrence] = Cell(1, entrence, 'R');
	labyrinth.setRobotCoordinates(1, entrence);

	matrix = findPath(labyrinth, matrix);

	// postavljanje predmeta
	for (int i = 0; i < labyrinth.getItemNumber(); i++) {
		while (true) {
			int randRow = 1 + std::rand() % (labyrinth.getRows() - 2);
			int randCol = 1 + std::rand() % (labyrinth.getCols() - 2);
			// predmeti se dodaju na bilo kom prolazu
			if (matrix[randRow][randCol].getType() == '*' || matrix[randRow][randCol].getType() == '.') {
				matrix[randRow][randCol] = Cell(randRow, randCol, 'P');
				labyrinth.getItemList()[i] = SpecialItem(randRow, randCol, "");
				break;
			}
		}
	}

	// postavljanje minotaura
	while (true) {
		int randRow = 1 + std::rand() % (labyrinth.getRows() - 2);
		int randCol = 1 + std::rand() % (labyrinth.getCols() - 2);
		// minotaur se dodaje negde na siguran put
		if (matrix[randRow][randCol].getType() == '*') {
			matrix[randRow][randCol] = Cell(randRow, randCol, 'M');
			labyrinth.setMinotaurCoordinates(randRow, randCol);
			break;
		}
	}

	// svaka '*' postaje '.'
	for (unsigned int i = 0; i < labyrinth.getRows(); i++) {
		for (unsigned int j = 0; j < labyrinth.getCols(); j++) {
			if (matrix[i][j].getType() == '*') {
				matrix[i][j] = '.';
			}
		}
	}

	// prikaz vremena potrebnog za generisanje lavirinta
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "Matrix generated in " << duration.count() << " microseconds." << std::endl;
	return matrix;
}

Cell** findPath(Labyrinth& labyrinth, Cell** matrix) {
	/*
	Funkcija koja pronalazi siguran put kroz lavirint
	Parametri: referenca na lavirint, matrica tog lavirinta
	Povratna vrednost: matrica lavirinta
	*/

	int pathLength = 0;
	// nalazi put od ulaza do izlaza tako sto random bira sledecu poziciju (levo [0], dole [1], desno [2])
	unsigned int newRow = labyrinth.getRobotCoordinates()[0];
	unsigned int newCol = labyrinth.getRobotCoordinates()[1];
	// dok ne dodjemo do poslednjeg reda
	while (newRow <= labyrinth.getRows()) {
		int move = std::rand() % 3;
		unsigned int prevRow = newRow;
		unsigned int prevCol = newCol;
		switch (move) {
		case 0: {
			newCol--;
			break;
		}
		case 1: {
			newRow++;
			break;
		}
		case 2: {
			newCol++;
			break;
		}
		}

		if (newRow > 0 && newRow < labyrinth.getRows() - 1 && newCol > 0 && newCol < labyrinth.getCols() - 1) {
			// privremeno, siguran put obelezavam zvezdicom '*'
			matrix[newRow][newCol] = Cell(newRow, newCol, '*');
			pathLength++;
		}
		else if (newRow == labyrinth.getRows() - 1) {
			// ako smo u poslednjem redu, postavljamo izlaz na odabranu poziciju i prekidamo petlju
			matrix[newRow][newCol] = Cell(newRow, newCol, 'I');
			break;
		}
		else {
			// opcija van opsega, vracamo na pocetnu situaciju
			newRow = prevRow;
			newCol = prevCol;
		}
	}

	// ovde se racuna koji ce jos celija citi zidovi, a koliko prolaz

	// ukupan broj celija
	int cellNumber = labyrinth.getRows() * labyrinth.getCols();
	// oduzima se broj spoljasnjih zidova
	cellNumber = cellNumber - 2 * (labyrinth.getRows() + labyrinth.getCols()) + 4;
	// oduzima se minimalan broj unutrasnjih zidova
	cellNumber = cellNumber - 2 * (labyrinth.getRows() + labyrinth.getCols());
	// oduzima se duzina sigurnog puta
	cellNumber = cellNumber - pathLength;
	// polovina preostalih celija ce biti put, a druga polovina zidovi
	for (unsigned int i = 0; i < cellNumber / 2; i++) {
		while (true) {
			int randRow = 1 + std::rand() % (labyrinth.getRows() - 2);
			int randCol = 1 + std::rand() % (labyrinth.getCols() - 2);
			if (matrix[randRow][randCol].getType() == '#') {
				// put koji nije siguran (nasumicno dodate prolaze) obelezavamo tackom '.'
				matrix[randRow][randCol] = Cell(randRow, randCol, '.');
				break;
			}
		}
	}

	return matrix;
}