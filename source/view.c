#include "view.h"

static Views currentView = VIEW_TITLE_SCREEN;

Views get_view()
{
  return currentView;
}

void set_view(Views view)
{
  currentView = view;
}