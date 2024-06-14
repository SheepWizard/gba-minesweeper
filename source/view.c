#include "view.h"

static Views currentView = VIEW_HIGH_SCORES_MENU;

Views get_view()
{
  return currentView;
}

void set_view(Views view)
{
  currentView = view;
}