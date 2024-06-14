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

enum DotDisplaySide
{
  LEFT,
  RIGHT
};

void draw_dot_display(int number, enum DotDisplaySide side);