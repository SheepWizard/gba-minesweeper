#pragma once
#include "tonc.h"

#define CELL_SIZE 8
#define NEIGHBOUR_SIZE 8

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
  int clicks;
} Board;
