#pragma once
#include "tonc.h"

#define CELL_SIZE 8
#define NEIGHBOUR_SIZE 8
#define TOP_PADDING 20

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