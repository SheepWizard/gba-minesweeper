#include "dotDisplay.h"
#include "assets/number_0.h"
#include "assets/number_1.h"
#include "assets/number_2.h"
#include "assets/number_3.h"
#include "assets/number_4.h"
#include "assets/number_5.h"
#include "assets/number_6.h"
#include "assets/number_7.h"
#include "assets/number_8.h"
#include "assets/number_9.h"
#include "assets/number_blank.h"

static int NUMBER_WIDTH = 8;

static void draw_number(char number, int posX, int posY)
{
  const unsigned short *numberImage = number_0Bitmap;

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

  int y = 0;
  for (y = 0; y < 14; y++)
  {
    memcpy(&vid_mem[(y + posY) * M3_WIDTH + posX], &numberImage[y * 8], 16);
  }
}

void draw_dot_display(int number)
{
  number = clamp(number, -99, 999);
  char str[4];
  sprintf(str, "%d", number);
  int offset = 3 - strlen(str);

  int startX = 0;
  int i;
  for (i = 0; i < 3; i++)
  {
    if (i <= 3)
    {
      char tkn = str[i - offset];
      if (tkn == '-')
      {
        draw_number('-', startX, 0);
      }
      else
      {
        draw_number(tkn, startX, 0);
      }
    }
    else
    {
      draw_number('0', startX, 0);
    }
    startX += NUMBER_WIDTH;
  }
}
