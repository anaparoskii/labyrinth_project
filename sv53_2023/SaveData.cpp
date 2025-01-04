#include <iostream>
#include <string>
#include <fstream>
#include "SaveData.h"
#include "Labyrinth.h"

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
	std::ifstream file("lastGame.txt");
	if (!file.is_open()) {
		return 1;
	}
	int number;
	std::string line;
	file >> number;

	// broj poslednje igre
	return number;
}

int SaveData::saveGame(Labyrinth& labyrinth, bool won, bool lost) {
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