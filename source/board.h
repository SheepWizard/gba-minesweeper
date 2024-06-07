#pragma once
#include "common.h"
#include "selector.h"
#include "cell.h"
#include <stdlib.h>

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

void update_board(Board *board);
void free_board(Board *board);
void new_board(Board *board, int maxX, int maxY, int minesCount);