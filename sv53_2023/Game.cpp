#include <iostream>
#include <string>
#include "Cell.h"
#include "Labyrinth.h"
#include "Game.h"
#include "SaveData.h"
#include "SpecialItem.h"

/*
Modul koji sadrzi funkcije za tok igre
Autor: Ana Paroski
Poslednja izmena: 05.01.2025.
*/

Game::Game(Labyrinth& l) 
	: labyrinth(l), play(true), won(false), lost(false) {}

Game::Game(Labyrinth& l, bool play, bool won, bool lost) 
	: labyrinth(l), play(play), won(won), lost(lost) {}

Game::~Game() {}

Labyrinth& Game::getLabyrinth() {
	return this->labyrinth;
}
void Game::setLabyrinth(Labyrinth& labyrinth) {
	this->labyrinth = labyrinth;
}

bool Game::isPlay() {
	return this->play;
}
void Game::setPlay(bool play) {
	this->play = play;
}

bool Game::isWon() {
	return this->won;
}
void Game::setWon(bool won) {
	this->won = won;
}

bool Game::isLost() {
	return this->lost;
}
void Game::setLost(bool lost) {
	this->lost = lost;
}

void Game::startGame() {
	/*
	Ova funkcija sadrzi petlju koja omogacava nastavak igre sve dok je parametar play = true
	*/

	while (play) {
		updateActiveItems();
		showMatrix();
		char move;
		// korisnik bira potez
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
			moved = robotMove(newRow, newCol);
		}
		if (!play) break;
		if (moved) {
			// logika za pomeranje minotaura 'M'
			bool minotaurMoved = false;
			int mRow = labyrinth.getMinotaurCoordinates()[0];
			int mCol = labyrinth.getMinotaurCoordinates()[1];
			int rRow = labyrinth.getRobotCoordinates()[0];
			int rCol = labyrinth.getRobotCoordinates()[1];
			
			minotaurMoved = robotCollision(rRow, rCol, mRow, mCol);
			// ako nije pored robota, bira se nasumican potez
			while (!minotaurMoved) {
				int minotaurMove = std::rand() % 4;  // 4 moguca poteza - A (levo), W (gore), S (dole), D (desno)
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
					if (labyrinth[newRow][newCol].getType() != '#'
						&& labyrinth[newRow][newCol].getType() != 'I'
						&& labyrinth[newRow][newCol].getType() != 'U') {
						// logika za kupljenje predmeta 'P'
						// minotaur samo unisti predmet tako da nema potrebe za dodatnom logikom
						labyrinth[mRow][mCol] = '.';
						if (labyrinth[newRow][newCol].getType() == 'P') {
							for (int i = 0; i < labyrinth.getItemNumber(); i++) {
								if (labyrinth.getItemList()[i].getX() == newRow && labyrinth.getItemList()[i].getY() == newCol) {
									labyrinth.getItemList()[i].setX(-1);
									labyrinth.getItemList()[i].setY(-1);
									break;
								}
							}
							std::cout << "Minotaur destroyed an object!" << std::endl;
						}
						labyrinth[newRow][newCol] = 'M';
						labyrinth.setMinotaurCoordinates(newRow, newCol);
						minotaurMoved = true;
					}
				}
				if (minotaurMoved) break;
			}
		}
	}
	handleEnd();
}

void Game::updateActiveItems() {
	for (int i = 0; i < labyrinth.getItemNumber(); i++) {
		if (labyrinth.getItemList()[i].isActive()) {
			labyrinth.getItemList()[i].setMovesLeft(labyrinth.getItemList()[i].getMovesLeft() - 1);
			if (labyrinth.getItemList()[i].getMovesLeft() == 0) {
				labyrinth.getItemList()[i].setActive(false);
				labyrinth.getItemList()[i].setX(-1);
				labyrinth.getItemList()[i].setY(-1);
			}
		}
	}
}

void Game::showMatrix() {
	if (isFogActive(labyrinth.getItemList(), labyrinth.getItemNumber())) {
		labyrinth.showFogMatrix();
	}
	else {
		labyrinth.showMatrix();
	}
}

void Game::wallCollision(int currentRobotX, int currentRobotY, int newRobotX, int newRobotY) {
	/*
	Funkcija koja se bavi situacijom kada robot treba da prodje kroz zid
	Ako nam nije aktiviran cekic, ovo nece biti moguce
	Parametri: vrednosti starih i potencijalnih novih koordinata robota
	*/
	if (isHammerActive(labyrinth.getItemList(), labyrinth.getItemNumber())) {
		labyrinth[currentRobotX][currentRobotY] = '.';
		labyrinth[newRobotX][newRobotY] = 'R';
		labyrinth.setRobotCoordinates(newRobotX, newRobotY);
		std::cout << "You destroyed a wall!!!" << std::endl;
	}
	else {
		std::cout << "You can't walk through walls..." << std::endl;
	}
}

void Game::minotaurCollision(int currentRobotX, int currentRobotY, int newRobotX, int newRobotY) {
	/*
	Funkcija koja se bavi situacijom kada robot krene na minotaura
	Ako nam nije aktiviran mac, minotaur ce unistiti robota
	Parametri: vrednosti starih i potencijalnih novih koordinata robota
	*/
	if (isSwordActive(labyrinth.getItemList(), labyrinth.getItemNumber())) {
		labyrinth[currentRobotX][currentRobotY] = '.';
		labyrinth[newRobotX][newRobotY] = 'R';
		labyrinth.setRobotCoordinates(newRobotX, newRobotY);
		labyrinth.setMinotaurCoordinates(-1, -1);
		std::cout << "You killed the minotaur!!!" << std::endl;
	}
	else {
		labyrinth[currentRobotX][currentRobotY] = '.';
		labyrinth.setRobotCoordinates(-1, -1);
		play = false;
		lost = true;
	}
}

void Game::itemCollection(int currentRobotX, int currentRobotY, int newRobotX, int newRobotY) {
	/*
	Funkcija koja omogucava kupljenje predmeta na tabli
	Parametri: vrednosti starih i novih koordinata robota
	*/
	labyrinth[currentRobotX][currentRobotY] = '.';

	// bira se nasumicno koji ce predmet biti aktivan
	int randomItem = std::rand() % 4;
	int itemIndex = -1;
	for (int i = 0; i < labyrinth.getItemNumber(); i++) {
		if (labyrinth.getItemList()[i].getX() == newRobotX && labyrinth.getItemList()[i].getY() == newRobotY) {
			itemIndex = i;
			break;
		}
	}
	switch (randomItem) {
	case 0: {
		labyrinth.getItemList()[itemIndex] = labyrinth.getItemList()[itemIndex].activateFogOfWar();
		break;
	}
	case 1: {
		labyrinth.getItemList()[itemIndex] = labyrinth.getItemList()[itemIndex].activateSword();
		break;
	}
	case 2: {
		labyrinth.getItemList()[itemIndex] = labyrinth.getItemList()[itemIndex].activateShield();
		break;
	}
	case 3: {
		labyrinth.getItemList()[itemIndex] = labyrinth.getItemList()[itemIndex].activateHammer();
		break;
	}
	}
	labyrinth[newRobotX][newRobotY] = 'R';
	labyrinth.setRobotCoordinates(newRobotX, newRobotY);
}

bool Game::robotCollision(int robotX, int robotY, int minotaurX, int minotaurY) {
	/*
	Funkcija koja se bavi situacijom gde minotaur unistava robota ako se nalazi pored njega
	Parametri: trenutne koordinate robota i minotaura
	Povratna vrednost: bool da li se minotaur pomerio ili nije
	*/
	if ((minotaurX == robotX && (minotaurY + 1 == robotY || minotaurY - 1 == robotY))
		|| (minotaurY == robotY && (minotaurX + 1 == robotX || minotaurX - 1 == robotX))) {
		if (isShieldActive(labyrinth.getItemList(), labyrinth.getItemNumber())) {
			std::cout << "You stopped the minotaur!!!" << std::endl;
		}
		else {
			labyrinth[robotX][robotY] = 'M';
			labyrinth[minotaurX][minotaurY] = '.';
			labyrinth.setMinotaurCoordinates(robotX, robotY);
			labyrinth.setRobotCoordinates(-1, -1);
			lost = true;
			play = false;
		}
		return true;
	}
	return false;
}

bool Game::robotMove(int newRobotX, int newRobotY) {
	/*
	Funkcija koja se bavi kretanjem robota
	*/
	unsigned int x = labyrinth.getRobotCoordinates()[0];
	unsigned int y = labyrinth.getRobotCoordinates()[1];
	if (labyrinth[newRobotX][newRobotY].getType() == '#') {
		wallCollision(x, y, newRobotX, newRobotY);
	}
	else if (labyrinth[newRobotX][newRobotY].getType() == 'M') {
		minotaurCollision(x, y, newRobotX, newRobotY);
	}
	else if (labyrinth[newRobotX][newRobotY].getType() == 'P') {
		itemCollection(x, y, newRobotX, newRobotY);
	}
	else {
		labyrinth[x][y] = '.';
		if (labyrinth[newRobotX][newRobotY].getType() == 'I') {
			won = true;
			play = false;
		}
		labyrinth[newRobotX][newRobotY] = 'R';
		labyrinth.setRobotCoordinates(newRobotX, newRobotY);
	}
	return true;
}

void Game::handleEnd() {
	/*
	Funkcija koja obezbedjuje kraj igre, proverava se ima li pobednika i rezultat se cuva u .txt fajl
	*/
	if (won) {
		labyrinth.showMatrix();
		std::cout << "You got out!!!" << std::endl;
	}
	else if (lost) {
		labyrinth.showMatrix();
		std::cout << "Minotaur caught you! :(" << std::endl;
	}
	// cuvanje igre u fajl
	SaveData saveData;
	saveData.saveGame(labyrinth, won, lost);
}

bool Game::isSwordActive(SpecialItem* itemList, int length) {
	for (int i = 0; i < length; i++) {
		if (itemList[i].isActive() && itemList[i].getItemName() == "sword") {
			return true;
		}
	}
	return false;
}

bool Game::isHammerActive(SpecialItem* itemList, int length) {
	for (int i = 0; i < length; i++) {
		if (itemList[i].isActive() && itemList[i].getItemName() == "hammer") {
			return true;
		}
	}
	return false;
}

bool Game::isShieldActive(SpecialItem* itemList, int length) {
	for (int i = 0; i < length; i++) {
		if (itemList[i].isActive() && itemList[i].getItemName() == "shield") {
			return true;
		}
	}
	return false;
}

bool Game::isFogActive(SpecialItem* itemList, int length) {
	for (int i = 0; i < length; i++) {
		if (itemList[i].isActive() && itemList[i].getItemName() == "fog of war") {
			return true;
		}
	}
	return false;
}