#pragma once
#include <stdlib.h>
#include "save.h"

typedef enum
{
  SAVE_BEGINNER,
  SAVE_INTERMEDIATE,
  SAVE_EXPERT
} ScoreSave;

typedef struct HighScores
{
  int beginnerScores[MAX_SCORES];
  int intermediateScores[MAX_SCORES];
  int expertScores[MAX_SCORES];
} HighScores;

void save_score(const ScoreSave type, const int score);
int read_scores(HighScores *highScores);
