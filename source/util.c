#include "util.h"

void key_wait_till_clear_debounce(u16 key, int debounce)
{
  int count = 0;
  while (1)
  {
    vid_vsync();
    key_poll();
    if (key_is_up(key))
      break;
  }
  while (count < debounce)
  {
    vid_vsync();
    count++;
  }
}