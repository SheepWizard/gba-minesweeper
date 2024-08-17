#include "menuView.h"

static int selectorPosition = 0;

static void update_menu_selector(const int previousPosition)
{
  int yOffset = (SELECTOR_GAP * previousPosition) + SELECTOR_Y_OFFSET;

  int i;
  for (i = 0; i < SELECTOR_SIZE; i++)
  {
    memcpy(&vid_mem[(i + yOffset) * M3_WIDTH + SELECTOR_X_OFFSET], &menu_screenBitmap[(i + yOffset) * (M3_WIDTH / 2) + (SELECTOR_X_OFFSET / 2)], SELECTOR_SIZE * 2);
  }

  yOffset = (SELECTOR_GAP * selectorPosition) + SELECTOR_Y_OFFSET;
  for (i = 0; i < SELECTOR_SIZE; i++)
  {
    memcpy(&vid_mem[(i + yOffset) * M3_WIDTH + SELECTOR_X_OFFSET], &smiley_playBitmap[i * (SELECTOR_SIZE / 2)], SELECTOR_SIZE * 2);
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

  if (key_hit(KEY_START))
  {
    set_view(VIEW_TITLE_SCREEN);
  }

  if (key_released(KEY_A))
  {
    select_option();
  }
}
