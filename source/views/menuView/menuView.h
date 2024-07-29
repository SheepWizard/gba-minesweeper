#pragma once
#include "tonc.h"
#include "../../assets/menu_screen.h"
#include "../../assets/cursor.h"
#include "../../view.h"
#include "../gameView/gameView.h"
#include <string.h>

static const int SELECTOR_SIZE = 24;
static const int SELECTOR_GAP = 25;

void init_menu_view();
void update_menu_view();