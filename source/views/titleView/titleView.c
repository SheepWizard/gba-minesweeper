#include "titleView.h"

void init_title_view()
{
  memcpy(vid_mem, title_screenBitmap, M3_SIZE);
}

void update_title_view()
{
  if (key_hit(KEY_START))
  {
    set_view(VIEW_GAME);
  }
}