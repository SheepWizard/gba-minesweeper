#include "common.h"
#include <string.h>
#include "assets/cell_hidden.h"
#include "assets/cell_1.h"
#include "assets/cell_2.h"
#include "assets/cell_3.h"
#include "assets/cell_4.h"
#include "assets/cell_5.h"
#include "assets/cell_6.h"
#include "assets/cell_7.h"
#include "assets/cell_8.h"
#include "assets/cell_open.h"
#include "assets/cell_mine.h"

void create_cell(int x, int y, int number, int isMine, Cell *myCell)
{
  myCell->x = x;
  myCell->y = y;
  myCell->number = number;
  myCell->isMine = isMine;
  myCell->isFlagged = 0;
  myCell->isOpen = 0;
}

void draw_cell(Cell *inCell)
{

  const unsigned short *cellImage = cell_hiddenBitmap;

  if (inCell->isOpen)
  {
    if (inCell->isMine)
    {
      cellImage = cell_mineBitmap;
    }
    else
    {
      switch (inCell->number)
      {
      case 0:
        cellImage = cell_openBitmap;
        break;
      case 1:
        cellImage = cell_1Bitmap;
        break;
      case 2:
        cellImage = cell_2Bitmap;
        break;
      case 3:
        cellImage = cell_3Bitmap;
        break;
      case 4:
        cellImage = cell_4Bitmap;
        break;
      case 5:
        cellImage = cell_5Bitmap;
        break;
      case 6:
        cellImage = cell_6Bitmap;
        break;
      case 7:
        cellImage = cell_7Bitmap;
        break;
      case 8:
        cellImage = cell_8Bitmap;
        break;
      default:
        cellImage = cell_openBitmap;
        break;
      }
    }
  }
  else
  {
    cellImage = cell_hiddenBitmap;
  }

  int yOffset = 8 * inCell->y;
  int xOffset = 8 * inCell->x;
  int y = 0;
  for (y = 0; y < 8; y++)
  {
    memcpy(&vid_mem[(y + yOffset) * M3_WIDTH + xOffset], &cellImage[y * 8], 16);
  }
}