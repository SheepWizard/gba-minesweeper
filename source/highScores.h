#pragma once
#include <stdlib.h>
#include "save.h"

typedef enum
{
  SAVE_BEGINNER,
  SAVE_INTERMEDIATE,
  SAVE_EXPERT
} ScoreSave;

void save_score(const ScoreSave type, const u32 score);
volatile SaveData *read_scores();