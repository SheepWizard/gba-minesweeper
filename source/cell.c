#include "cell.h"

void create_cell(int x, int y, Cell *cell)
{
  cell->x = x;
  cell->y = y;
  cell->number = 0;
  cell->isMine = false;
  cell->isFlagged = false;
  cell->isOpen = false;
  cell->mineHit = false;
  cell->hovered = false;
}

void flag_cell(Cell *cell)
{
  if (cell->isOpen)
  {
    return;
  }

  cell->isFlagged = cell->isFlagged ? false : true;
}

void draw_cell(Cell *inCell, int maxX, int maxY)
{

  const unsigned int *cellImage = cell_hiddenBitmap;

  if (inCell->isOpen)
  {
    if (inCell->isMine)
    {
      if (inCell->mineHit)
      {
        cellImage = cell_minehitBitmap;
      }
      else
      {
        cellImage = cell_mineBitmap;
      }
    }
    else if (inCell->isFlagged && !inCell->isMine)
    {
      cellImage = cell_wrongflagBitmap;
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
  else if (inCell->isFlagged)
  {
    cellImage = cell_flagBitmap;
  }
  else
  {
    if (inCell->hovered)
    {
      cellImage = cell_hoveredBitmap;
    }
    else
    {
      cellImage = cell_hiddenBitmap;
    }
  }

  int xCenter = (M3_WIDTH / 2) - (maxX * CELL_SIZE) / 2;
  int yCenter = (M3_HEIGHT / 2) - (maxY * CELL_SIZE) / 2;

  int yOffset = CELL_SIZE * inCell->y + yCenter + (TOP_PADDING * 2);
  int xOffset = CELL_SIZE * inCell->x + xCenter;
  int y;
  for (y = 0; y < CELL_SIZE; y++)
  {
    memcpy(&vid_mem[(y + yOffset) * M3_WIDTH + xOffset], &cellImage[y * (CELL_SIZE / 2)], CELL_SIZE * 2);
  }
}