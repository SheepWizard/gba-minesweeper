#pragma once
#include "seed.h"
#include "views/titleView/titleView.h"
#include "views/gameView/gameView.h"
#include "views/menuView/menuView.h"
#include "views/scoresView/scoresView.h"

typedef enum
{
  VIEW_TITLE_SCREEN,
  VIEW_MAIN_MENU,
  VIEW_GAME,
  VIEW_HIGH_SCORES_MENU,
} Views;

Views get_view();
void set_view(Views view);
void watch_view();