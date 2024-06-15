#pragma once
#include "common.h"
#include <string.h>
#include "assets/cell_hidden.h"
#include "assets/cell_1.h"
#include "assets/cell_2.h"
#include "assets/cell_3.h"
#include "assets/cell_4.h"
#include "assets/cell_5.h"
#include "assets/cell_6.h"
#include "assets/cell_7.h"
#include "assets/cell_8.h"
#include "assets/cell_open.h"
#include "assets/cell_hovered.h"
#include "assets/cell_mine.h"
#include "assets/cell_flag.h"
#include "assets/cell_minehit.h"
#include "assets/cell_wrongflag.h"

static const int CELL_SIZE = 8;

typedef struct Cell
{
  int x;
  int y;
  int number;
  bool isMine;
  bool isFlagged;
  bool isOpen;
  bool mineHit;
  bool hovered;
} Cell;

void create_cell(int x, int y, Cell *cell);
void flag_cell(Cell *cell);
void draw_cell(Cell *inCell, int maxX, int maxY);