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

void reset_selector()
{
  posX = 0;
  posY = 0;
}

void draw_selector(int maxX, int maxY)
{
  int xOffset = (M3_WIDTH / 2) - (maxX * CELL_SIZE) / 2;
  int yOffset = (M3_HEIGHT / 2) - (maxY * CELL_SIZE) / 2;
  m3_frame(posX * CELL_SIZE + xOffset, posY * CELL_SIZE + yOffset, posX * CELL_SIZE + CELL_SIZE + xOffset, posY * CELL_SIZE + CELL_SIZE + yOffset, CLR_PURPLE);
}