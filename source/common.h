#pragma once
#include "tonc.h"

typedef struct Cell
{
  int x;
  int y;
  int number;
  bool isMine;
  bool isFlagged;
  bool isOpen;
} Cell;

typedef struct Board
{
  Cell *cells;
  int maxX;
  int maxY;
  int minesCount;
  int flagsPlaced;
  int nonMineCellsOpened;
  bool gameOver;
  int hitMine;
} Board;
