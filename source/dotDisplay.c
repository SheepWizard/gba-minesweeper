#include "dotDisplay.h"
#include "assets/number_0.h"

void draw_number(int number, int posX, int posY)
{
  int y = 0;
  for (y = 0; y < 14; y++)
  {
    memcpy(&vid_mem[(y + posY) * M3_WIDTH + posX], &number_0Bitmap[y * 8], 16);
  }
}