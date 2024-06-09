#pragma once
#include <stdlib.h>
#include "save.h"

enum SCORES_SAVE
{
  SAVE_BEGINNER,
  SAVE_INTERMEDIATE,
  SAVE_EXPERT
};

void save_score(const enum SCORES_SAVE type, const u8 score);
