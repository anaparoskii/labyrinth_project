#pragma once
#include "Cell.h"

class Labyrinth {
	/*
	Klasa koja predstavlja lavirint
	Autor: Ana Paroski
	Poslednja izmena: 04.01.2025.
	*/
private:
	Cell** matrix;  // dvodimenzionalni niz (matrica)
	unsigned int rows;  // broj redova matrice
	unsigned int cols;  // broj kolona matrice
	int itemNumber;  // broj specijalnih elemenata u lavirintu
	int robotCoordinates[2];  // niz od 2 elementa koji cuva trenutne koordinate robota
	int minotaurCoordinates[2];  // niz od 2 elementa koji cuva trenutne koordinate minotaura

public:
	// konstruktori i destruktor
	Labyrinth();
	Labyrinth(unsigned int rows, unsigned int cols, int itemNumber);
	~Labyrinth();

	// getteri i setteri za sve atribute klase
	unsigned int getRows();
	void setRows(unsigned int rows);

	unsigned int getCols();
	void setCols(unsigned int cols);

	int getItemNumber();
	void setItemNumber(int itemNumber);

	int* getRobotCoordinates();
	void setRobotCoordinates(int row, int col);

	int* getMinotaurCoordinates();
	void setMinotaurCoordinates(int row, int col);

	// matrica ima samo getter jer se ona inicijalizuje u konstruktoru pomocu modula GenerateLabyrinth
	Cell** getMatrix();

	// preklopljen operator []
	Cell* operator[](unsigned int row);

	// funkcija koja ispisuje matricu u konzoli
	void showMatrix();
};
