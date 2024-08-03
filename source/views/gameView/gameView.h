#pragma once
#include "../../board.h"
#include "../../view.h"
#include "../../util.h"
#include "../../assets/game_background.h"
#include <string.h>

void set_difficulty(Difficulty difficulty);
void update_game_view();
void init_game_view();
void close_game_view();