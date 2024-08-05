#pragma once
#include "tonc.h"
#include <string.h>
#include "../../highScores.h"
#include "../../view.h"
#include "../../assets/highscore_screen.h"

static const int SCORES_PER_PAGE = 5;

typedef enum
{
  SCORES_PAGE_BEGINNER,
  SCORES_PAGE_INTERMEDIATE,
  SCORES_PAGE_EXPERT
} ScoresPage;

void init_scores_view();
void update_scores_view();