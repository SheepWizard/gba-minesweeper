#pragma once
#include "tonc.h"
#include "common.h"
#include <string.h>
#include "assets/smiley_play.h"
#include "assets/smiley_oface.h"
#include "assets/smiley_dead.h"
#include "assets/smiley_win.h"

enum Smiles
{
  SMILE_DEAD,
  SMILE_OFACE,
  SMILE_PLAY,
  SMILE_WIN
};

void draw_smile(enum Smiles smile);