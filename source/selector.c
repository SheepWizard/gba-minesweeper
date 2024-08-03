#include "selector.h"

static int posX = 0;
static int posY = 0;

Selector update_selector(const int maxX, const int maxY)
{
  if (key_hit(KEY_RIGHT) || key_held_right())
  {
    posX++;
  }
  if (key_hit(KEY_LEFT) || key_held_left())
  {
    posX--;
  }
  if (key_hit(KEY_UP) || key_held_up())
  {
    posY--;
  }
  if (key_hit(KEY_DOWN) || key_held_down())
  {
    posY++;
  }

  if (posX >= maxX)
  {
    posX = 0;
  }
  if (posX < 0)
  {
    posX = maxX - 1;
  }
  if (posY >= maxY)
  {
    posY = 0;
  }
  if (posY < 0)
  {
    posY = maxY - 1;
  }

  Selector selector;
  selector.posX = posX;
  selector.posY = posY;

  return selector;
}

void reset_selector(const int maxX, const int maxY)
{
  posX = maxX / 2;
  posY = maxY / 2;
}

Selector get_selector_position()
{
  Selector s;
  s.posX = posX;
  s.posY = posY;
  return s;
}

void draw_selector(int maxX, int maxY)
{
  int xOffset = (M3_WIDTH / 2) - (maxX * CELL_SIZE) / 2;
  int yOffset = (M3_HEIGHT / 2) - (maxY * CELL_SIZE) / 2 + (TOP_PADDING * 2);
  m3_frame(posX * CELL_SIZE + xOffset, posY * CELL_SIZE + yOffset, posX * CELL_SIZE + CELL_SIZE + xOffset, posY * CELL_SIZE + CELL_SIZE + yOffset, RGB15(0, 0, 0));
}