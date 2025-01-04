#pragma once
#include <iostream>
#include "Cell.h"
#include "Labyrinth.h"

Cell** generateLabyrinth(Labyrinth& labyrinth);

Cell** findPath(Labyrinth& labyrinth, Cell** matrix);
