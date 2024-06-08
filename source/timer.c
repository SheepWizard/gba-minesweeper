#include "timer.h"

static u32 time = 0;
static int vblankCount = 0;
static bool running = false;

void start_timer()
{
  time = 0;
  running = true;
}

u32 read_timer()
{
  if (!running)
  {
    return time;
  }
  vblankCount++;
  if (vblankCount % 59 == 0)
  {
    time++;
    vblankCount = 0;
  }
  return time;
}

void stop_timer()
{
  running = false;
}