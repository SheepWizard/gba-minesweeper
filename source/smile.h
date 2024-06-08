#pragma once
#include "tonc.h"
#include <string.h>

enum Smiles
{
  SMILE_DEAD,
  SMILE_OFACE,
  SMILE_PLAY,
  SMILE_WIN
};

void draw_smile(enum Smiles smile);