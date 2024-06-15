#include "menuView.h"

static const int SELECTOR_GAP = 20;
static const int MAX_SELECTOR_POSITION = 3;
static int selectorPosition = 0;

// Make this better
static void update_menu_selector(const int previousPosition)
{
  int yOffset = (10 * previousPosition) + 30 + (SELECTOR_GAP * previousPosition);

  int i;
  for (i = 0; i < 10; i++)
  {
    memcpy(&vid_mem[(i + yOffset) * M3_WIDTH + 20], &menu_screenBitmap[(i + yOffset) * M3_WIDTH + 20], 20);
  }

  yOffset = (10 * selectorPosition) + 30 + (SELECTOR_GAP * selectorPosition);
  for (i = 0; i < 10; i++)
  {
    memcpy(&vid_mem[(i + yOffset) * M3_WIDTH + 20], &cursorBitmap[i * 10], 20);
  }
}

static void select_option()
{
  switch (selectorPosition)
  {
  case 0:
    set_difficulty(DIFFICULTY_BEGINNER);
    set_view(VIEW_GAME);
    break;
  case 1:
    set_difficulty(DIFFICULTY_INTERMEDIATE);
    set_view(VIEW_GAME);
    break;
  case 2:
    set_difficulty(DIFFICULTY_EXPERT);
    set_view(VIEW_GAME);
    break;
  case 3:
    set_view(VIEW_HIGH_SCORES_MENU);
    break;
  }
}

void init_menu_view()
{
  memcpy(vid_mem, menu_screenBitmap, M3_SIZE);
  update_menu_selector(selectorPosition);
}

void update_menu_view()
{

  if (key_hit(KEY_DOWN))
  {
    int oldPosition = selectorPosition;
    if (selectorPosition == MAX_SELECTOR_POSITION)
    {
      selectorPosition = 0;
    }
    else
    {
      selectorPosition++;
    }
    update_menu_selector(oldPosition);
  }

  if (key_hit(KEY_UP))
  {
    int oldPosition = selectorPosition;
    if (selectorPosition == 0)
    {
      selectorPosition = MAX_SELECTOR_POSITION;
    }
    else
    {
      selectorPosition--;
    }
    update_menu_selector(oldPosition);
  }

  if (key_released(KEY_A))
  {
    select_option();
  }
}
