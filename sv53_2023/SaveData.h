#pragma once
#include <iostream>
#include <string>
#include "Labyrinth.h"

class SaveData {
	/*
	Klasa koja omogucava cuvanje poslednje odigrane igre u .txt fajl
	Autor: Ana Paroski
	Poslednja izmena: 04.01.2025.
	*/
private:
	int gameNumber;  // redni broj trenutne igre
	std::string fileName;  // ime fajla u koji ce igra da se sacuva

public:
	// konstruktor i destruktor
	SaveData();
	~SaveData();

	// getteri i setteri za sve atribute klase
	int getGameNumber();
	void setGameNumber(int number);

	std::string getFileName();
	void setFileName(std::string name);

	// funkcija koja vraca redni broj prethodne odigrane igre
	int getLastGame();

	// funkcija koja obavlja upisivanje u fajl
	int saveGame(Labyrinth& labyrinth, bool won, bool lost);

};
