#pragma once
#include <stdlib.h>
#include "save.h"

enum SCORES_SAVE
{
  SAVE_BEGINNER,
  SAVE_INTERMEDIATE,
  SAVE_EXPERT
};

typedef struct HighScores
{
  int beginnerScores[MAX_SCORES];
  int intermediateScores[MAX_SCORES];
  int expertScores[MAX_SCORES];
} HighScores;

void save_score(const enum SCORES_SAVE type, const int score);
int read_scores(HighScores *highScores);
