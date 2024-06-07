#pragma once
#include "common.h"

typedef struct Board
{
  Cell *cells;
  int maxX;
  int maxY;
  int minesCount;
  int flagsPlaced;
  int nonMineCellsOpened;
  bool gameOver;
  int clicks;
} Board;

void update_board();