#pragma once
#include <string.h>
#include "common.h"
#include "tonc.h"

enum DotDisplaySide
{
  LEFT,
  RIGHT
};

void draw_dot_display(int number, enum DotDisplaySide side);