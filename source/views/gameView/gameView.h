#pragma once
#include "../../board.h"
#include "../../selector.h"
#include "../../view.h"

typedef enum
{
  DIFFICULTY_BEGINNER,
  DIFFICULTY_INTERMEDIATE,
  DIFFICULTY_EXPERT
} Difficulty;

void set_difficulty(Difficulty difficulty);
void update_game_view();
void init_game_view();