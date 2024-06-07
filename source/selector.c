#include "selector.h"

static int posX = 0;
static int posY = 0;

Selector update_selector(Board *board)
{
  if (key_hit(KEY_RIGHT))
  {
    posX++;
  }
  if (key_hit(KEY_LEFT))
  {
    posX--;
  }
  if (key_hit(KEY_UP))
  {
    posY--;
  }
  if (key_hit(KEY_DOWN))
  {
    posY++;
  }

  if (posX >= board->maxX)
  {
    posX = 0;
  }
  if (posX < 0)
  {
    posX = board->maxX - 1;
  }
  if (posY >= board->maxY)
  {
    posY = 0;
  }
  if (posY < 0)
  {
    posY = board->maxY - 1;
  }

  Selector selector;
  selector.posX = posX;
  selector.posY = posY;

  return selector;
}

void draw_selector()
{
  m3_frame(posX * CELL_SIZE, posY * CELL_SIZE, posX * CELL_SIZE + CELL_SIZE, posY * CELL_SIZE + CELL_SIZE, CLR_PURPLE);
}