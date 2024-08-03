#pragma once
#include "tonc.h"

static const int KEY_HELD_DELAY = 8;

void key_held_update();
bool key_held_up();
bool key_held_down();
bool key_held_left();
bool key_held_right();