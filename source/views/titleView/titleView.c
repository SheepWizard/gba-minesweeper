#include "titleView.h"

static int count = 0;
static bool firstScreen = true;

static void draw_title()
{
  if (firstScreen)
  {
    memcpy(vid_mem, title_screenBitmap, M3_SIZE);
  }
  else
  {
    memcpy(vid_mem, title_screen2Bitmap, M3_SIZE);
  }
}

void init_title_view()
{
  draw_title();
}

void update_title_view()
{
  if (key_hit(KEY_START))
  {
    set_view(VIEW_MAIN_MENU);
  }
  count++;
  if (count % 35 == 0)
  {
    firstScreen = !firstScreen;
    draw_title();
  }
}