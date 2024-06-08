#pragma once
#include "common.h"

#define CELL_SIZE 8

typedef struct Cell
{
  int x;
  int y;
  int number;
  bool isMine;
  bool isFlagged;
  bool isOpen;
  bool mineHit;
} Cell;

void create_cell(int x, int y, Cell *cell);
void flag_cell(Cell *cell);
void draw_cell(Cell *inCell, int maxX, int maxY);