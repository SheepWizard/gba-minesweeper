#pragma once
#include "common.h"
#include "selector.h"
#include "cell.h"
#include "dotDisplay.h"
#include "timer.h"
#include "smile.h"
#include "highScores.h"
#include <stdlib.h>

typedef enum
{
  DIFFICULTY_BEGINNER,
  DIFFICULTY_INTERMEDIATE,
  DIFFICULTY_EXPERT
} Difficulty;

typedef struct
{
  Cell *cells;
  int maxX;
  int maxY;
  int minesCount;
  int flagsPlaced;
  int nonMineCellsOpened;
  bool gameOver;
  int clicks;
  int time;
  Difficulty difficulty;
} Board;

void update_board(Board *board);
void free_cells(Board *board);
void new_board(Board *board, int maxX, int maxY, int minesCount, Difficulty difficulty);