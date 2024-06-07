#pragma once

#include "tonc.h"
#include "board.h"

typedef struct Selector
{
  int posX;
  int posY;
} Selector;

Selector update_selector();
void draw_selector();