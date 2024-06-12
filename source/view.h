#pragma once

typedef enum
{
  VIEW_TITLE_SCREEN,
  VIEW_MAIN_MENU,
  VIEW_GAME,
  VIEW_HIGH_SCORES_MENU,
} Views;

static Views currentView = VIEW_TITLE_SCREEN;

void set_view(Views view);