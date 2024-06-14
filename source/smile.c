#include "smile.h"

void draw_smile(enum Smiles smile)
{
  const unsigned short *smileImage = smiley_playBitmap;

  switch (smile)
  {
  case SMILE_DEAD:
    smileImage = smiley_deadBitmap;
    break;
  case SMILE_OFACE:
    smileImage = smiley_ofaceBitmap;
    break;
  case SMILE_WIN:
    smileImage = smiley_winBitmap;
    break;
  default:
    break;
  }

  int posX = (M3_WIDTH / 2) - (14 / 2);
  int posY = TOP_PADDING;

  int y = 0;
  for (y = 0; y < 14; y++)
  {
    memcpy(&vid_mem[(y + posY) * M3_WIDTH + posX], &smileImage[y * 14], 28);
  }
}