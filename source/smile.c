#include "smile.h"

void draw_smile_frame()
{
  int posX = (M3_WIDTH / 2) - (SMILE_SIZE / 2);
  int posY = TOP_PADDING;

  m3_frame(posX - 1, posY - 1, posX + SMILE_SIZE + 1, posY + SMILE_SIZE + 1, FRAME_COLOUR);
  m3_frame(posX - 2, posY - 2, posX + SMILE_SIZE + 2, posY + SMILE_SIZE + 2, FRAME_COLOUR2);
}

void draw_smile_selector()
{
  int posX = (M3_WIDTH / 2) - (SMILE_SIZE / 2);
  int posY = TOP_PADDING;
  m3_frame(posX, posY, posX + SMILE_SIZE, posY + SMILE_SIZE, RGB15(31, 0, 0));
}

void draw_smile(Smiles smile)
{
  const unsigned int *smileImage = smiley_playBitmap;

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

  int posX = (M3_WIDTH / 2) - (SMILE_SIZE / 2);
  int posY = TOP_PADDING;

  int y = 0;
  for (y = 0; y < SMILE_SIZE; y++)
  {
    memcpy(&vid_mem[(y + posY) * M3_WIDTH + posX], &smileImage[y * (SMILE_SIZE / 2)], SMILE_SIZE * 2);
  }
}