#pragma once
#include <string.h>
#include "common.h"
#include "tonc.h"
#include "assets/number_0.h"
#include "assets/number_1.h"
#include "assets/number_2.h"
#include "assets/number_3.h"
#include "assets/number_4.h"
#include "assets/number_5.h"
#include "assets/number_6.h"
#include "assets/number_7.h"
#include "assets/number_8.h"
#include "assets/number_9.h"
#include "assets/number_blank.h"

typedef enum
{
  DOT_DISPLAY_SIDE_LEFT,
  DOT_DISPLAY_SIDE_RIGHT
} DotDisplaySide;

void draw_dot_display(int number, DotDisplaySide side);