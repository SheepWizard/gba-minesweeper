#include "dotDisplay.h"

void draw_dot_display_frames()
{
  int xOffset = (M3_WIDTH / 2) / 2 - (NUMBER_WIDTH * 3);
  int posY = TOP_PADDING;

  m3_frame(xOffset - 1, posY - 1, xOffset + (NUMBER_WIDTH * 3) + 1, posY + NUMBER_HEIGHT + 1, FRAME_COLOUR);
  xOffset = M3_WIDTH - (NUMBER_WIDTH * 3) + -xOffset;
  m3_frame(xOffset - 1, posY - 1, xOffset + (NUMBER_WIDTH * 3) + 1, posY + NUMBER_HEIGHT + 1, FRAME_COLOUR);
}

static void draw_number(const char number, const int posX)
{
  const unsigned int *numberImage = number_0Bitmap;

  switch (number)
  {
  case '1':
    numberImage = number_1Bitmap;
    break;
  case '2':
    numberImage = number_2Bitmap;
    break;
  case '3':
    numberImage = number_3Bitmap;
    break;
  case '4':
    numberImage = number_4Bitmap;
    break;
  case '5':
    numberImage = number_5Bitmap;
    break;
  case '6':
    numberImage = number_6Bitmap;
    break;
  case '7':
    numberImage = number_7Bitmap;
    break;
  case '8':
    numberImage = number_8Bitmap;
    break;
  case '9':
    numberImage = number_9Bitmap;
    break;
  case '-':
    numberImage = number_blankBitmap;
    break;
  default:
    break;
  }

  int posY = TOP_PADDING;
  int y = 0;
  for (y = 0; y < NUMBER_HEIGHT; y++)
  {
    memcpy(&vid_mem[(y + posY) * M3_WIDTH + posX], &numberImage[y * (NUMBER_WIDTH / 2)], NUMBER_WIDTH * 2);
  }
}

void draw_dot_display(int number, const DotDisplaySide side)
{
  number = clamp(number, -99, 999);
  char str[4];
  sprintf(str, "%d", number);
  int offset = 3 - strlen(str);

  int xOffset = (M3_WIDTH / 2) / 2 - (NUMBER_WIDTH * 3);
  int startX = xOffset;
  if (side == DOT_DISPLAY_SIDE_RIGHT)
  {
    startX = M3_WIDTH - (NUMBER_WIDTH * 3) + -xOffset;
  }
  int i;
  for (i = 0; i < 3; i++)
  {
    if (i <= 3)
    {
      char tkn = str[i - offset];
      if (tkn == '-')
      {
        draw_number('-', startX);
      }
      else
      {
        draw_number(tkn, startX);
      }
    }
    else
    {
      draw_number('0', startX);
    }
    startX += NUMBER_WIDTH;
  }
}
