#include <iostream>
#include <string>
#include <fstream>
#include "SaveData.h"
#include "Labyrinth.h"

/*
Modul koji sadrzi funkcije za rukovanje fajlova
Autor: Ana Paroski
Poslednja izmena: 04.01.2025.
*/

// konstruktor poziva funkciju getLastGame() i sam racuna redni broj sledece igre i na osnovu toga generise ime fajla
SaveData::SaveData() {
	int lastGameNumber = this->getLastGame();
	this->gameNumber = lastGameNumber + 1;
	this->fileName = "game" + std::to_string(this->gameNumber) + ".txt";
}

SaveData::~SaveData() {}

int SaveData::getGameNumber() {
	return this->gameNumber;
}

void SaveData::setGameNumber(int number) {
	this->gameNumber = number;
}

std::string SaveData::getFileName() {
	return this->fileName;
}

void SaveData::setFileName(std::string name) {
	this->fileName = name;
}

int SaveData::getLastGame() {
	/*
	Funkcija ucitava redni broj poslednje igre iz fajla lastGame.txt
	Povratna vrednost: redni broj poslednje igre
	*/
	std::ifstream file("lastGame.txt");
	if (!file.is_open()) {
		return -1;
	}
	int number;
	std::string line;
	file >> number;

	return number;
}

int SaveData::saveGame(Labyrinth& labyrinth, bool won, bool lost) {
	/*
	Funkcija cuva poslednju odigranu igru u fajl sa njenim rednim brojem, kao i u fajl lasyGame.txt
	U fajl se upisuje redni broj igre, stanje lavirinta nakon poslednjeg poteza i rezultat
	Parametri: refernca na lavirint, boolean vrednosti won i lost
	- bool won - true ako je robot pobedio (izasao iz lavirinta)
	- bool lost - true ako je minotaur pobedio (pojeo robota)
	- ako su oba false - robot je napustio igru
	Povratna vrednost: -1 ako je doslo do greske, 0 ako je sve izvrseno kako treba
	*/
	std::ofstream file(this->fileName);
	std::ofstream lastGameFile("lastGame.txt");
	if (!file.is_open()) {
		std::cout << "Error while opening file" << std::endl;
		return -1;
	}
	if (!lastGameFile.is_open()) {
		std::cout << "Error while opening last game file" << std::endl;
		return -1;
	}
	file << "Game " + std::to_string(this->gameNumber) << std::endl;
	lastGameFile << this->gameNumber << std::endl;
	for (unsigned int i = 0; i < labyrinth.getRows(); i++) {
		for (unsigned int j = 0; j < labyrinth.getCols(); j++) {
			file << labyrinth.getMatrix()[i][j].getType();
			lastGameFile << labyrinth.getMatrix()[i][j].getType();
		}
		file << std::endl;
		lastGameFile << std::endl;
	}
	file << std::endl;
	if (won) {
		file << "Result: robot won" << std::endl;
	    lastGameFile << "Result: robot won" << std::endl;
	}
	else if (lost) {
		file << "Result: minotaur won" << std::endl;
		lastGameFile << "Result: minotaur won" << std::endl;
	}
	else {
		file << "Result: robot quit the game" << std::endl;
		lastGameFile << "Result: robot quit the game" << std::endl;
	}

	file.close();
	lastGameFile.close();
	return 0;

}