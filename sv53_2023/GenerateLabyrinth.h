#pragma once
#include <iostream>
#include "Cell.h"
#include "Labyrinth.h"

/*
Modul koji sadrzi deklaracije funkcija koje generisu lavirint
Autor: Ana Paroski
Poslednja izmena: 04.01.2025.
*/

Cell** generateLabyrinth(Labyrinth& labyrinth);

Cell** findPath(Labyrinth& labyrinth, Cell** matrix);
