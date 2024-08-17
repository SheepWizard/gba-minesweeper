#pragma once
#include "tonc.h"
#include "../../assets/menu_screen.h"
#include "../../assets/smiley_play.h"
#include "../../view.h"
#include "../gameView/gameView.h"
#include <string.h>

static const int SELECTOR_SIZE = 16;
static const int SELECTOR_GAP = 25;
static const int SELECTOR_X_OFFSET = 16;
static const int SELECTOR_Y_OFFSET = 50;
static const int MAX_SELECTOR_POSITION = 3;

void init_menu_view();
void update_menu_view();