#pragma once
#include <iostream>
#include <string>
#include "Labyrinth.h"

class SaveData {
private:
	int gameNumber;
	std::string fileName;

public:
	SaveData();
	~SaveData();

	int getGameNumber();
	void setGameNumber(int number);

	std::string getFileName();
	void setFileName(std::string name);

	int getLastGame();

	int saveGame(Labyrinth& labyrinth, bool won, bool lost);

};
