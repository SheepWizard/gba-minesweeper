#pragma once
#include "common.h"

void create_cell(int x, int y, Cell *cell);
void flag_cell(Cell *cell);
void draw_cell(Cell *myCell, int maxX, int maxY);