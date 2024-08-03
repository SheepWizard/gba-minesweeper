#include "keyHeldUtil.h"

static int keyUpTime = KEY_HELD_DELAY;
static int keyDownTime = KEY_HELD_DELAY;
static int keyLeftTime = KEY_HELD_DELAY;
static int keyRightTime = KEY_HELD_DELAY;

void key_held_update()
{
  if (key_held(KEY_UP) && keyUpTime != 0)
  {
    keyUpTime--;
  }
  else
  {
    keyUpTime = KEY_HELD_DELAY;
  }

  if (key_held(KEY_DOWN) && keyDownTime != 0)
  {
    keyDownTime--;
  }
  else
  {
    keyDownTime = KEY_HELD_DELAY;
  }

  if (key_held(KEY_LEFT) && keyLeftTime != 0)
  {
    keyLeftTime--;
  }
  else
  {
    keyLeftTime = KEY_HELD_DELAY;
  }

  if (key_held(KEY_RIGHT) && keyRightTime != 0)
  {
    keyRightTime--;
  }
  else
  {
    keyRightTime = KEY_HELD_DELAY;
  }
}

bool key_held_up()
{
  return keyUpTime == 0;
}

bool key_held_down()
{
  return keyDownTime == 0;
}

bool key_held_left()
{
  return keyLeftTime == 0;
}

bool key_held_right()
{
  return keyRightTime == 0;
}