#pragma once

#include "tonc.h"
#include "common.h"
#include "board.h"

struct Board;

typedef struct Selector
{
  int posX;
  int posY;
} Selector;

Selector update_selector(struct Board *board);
void draw_selector(int maxX, int maxY);
void reset_selector();