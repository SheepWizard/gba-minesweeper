#pragma once
#include "save.h"
#include <string.h>
#include <stdlib.h>

typedef enum
{
  SAVE_BEGINNER,
  SAVE_INTERMEDIATE,
  SAVE_EXPERT
} ScoreSave;

void save_score(const ScoreSave type, const WinScore newScore);
SaveData *read_scores();