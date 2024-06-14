#pragma once
#include "tonc.h"
#include <string.h>
#include "../../highScores.h"
#include "../../view.h"

typedef enum
{
  SCORES_PAGE_BEGINNER,
  SCORES_PAGE_INTERMEDIATE,
  SCORES_PAGE_EXPERT
} ScoresPage;

void init_scores_view();
void update_scores_view();