#pragma once

typedef enum
{
  TITLE_SCREEN,
  MAIN_MENU,
  GAME,
  HIGH_SCORES_MENU,
} Views;

static Views currentView = TITLE_SCREEN;