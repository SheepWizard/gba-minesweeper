#pragma once

#include "tonc.h"
#include "common.h"
#include "board.h"

typedef struct Selector
{
  int posX;
  int posY;
} Selector;

Selector update_selector(const int maxX, const int maxY);
void draw_selector(int maxX, int maxY);
void reset_selector(const int maxX, const int maxY);
Selector get_selector_position();