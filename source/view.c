#include "view.h"

static Views currentView = VIEW_GAME;
static Views oldView = -1;

static void update_view()
{
  switch (currentView)
  {
  case VIEW_TITLE_SCREEN:
    update_title_view();
    break;
  case VIEW_GAME:
    update_game_view();
    break;
  case VIEW_MAIN_MENU:
    update_menu_view();
    break;
  case VIEW_HIGH_SCORES_MENU:
    update_scores_view();
    break;
  }
}

static void init_view()
{
  switch (currentView)
  {
  case VIEW_TITLE_SCREEN:
    init_title_view();
    break;
  case VIEW_GAME:
    init_game_view();
    break;
  case VIEW_MAIN_MENU:
    init_menu_view();
    break;
  case VIEW_HIGH_SCORES_MENU:
    init_scores_view();
    break;
  }
}

static void close_view()
{
  if (oldView == -1)
  {
    return;
  }

  switch (oldView)
  {
  case VIEW_TITLE_SCREEN:
    break;
  case VIEW_GAME:
    close_game_view();
    break;
  case VIEW_MAIN_MENU:
    break;
  case VIEW_HIGH_SCORES_MENU:
    break;
  }
}

Views get_view()
{
  return currentView;
}

void set_view(Views view)
{
  currentView = view;
}

void watch_view()
{
  if (oldView != currentView)
  {
    close_view();
    init_view();
    oldView = currentView;
  }
  update_view();
}
