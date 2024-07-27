#include "3bv.h"

void flood_fill(const Cell *cells, const int maxX, const int maxY, int x, int y, bool *marked)
{
  if (x < 0 || y < 0 || x >= maxX || y >= maxY)
  {
    return;
  }
  int index = y * maxX + x;
  if (marked[index] == true)
  {
    return;
  }
  marked[index] = true;

  if (cells[index].number != 0 || cells[index].isMine == true)
  {
    return;
  }

  y--;
  flood_fill(cells, maxX, maxY, x, y, marked);

  x++;
  flood_fill(cells, maxX, maxY, x, y, marked);

  y++;
  flood_fill(cells, maxX, maxY, x, y, marked);

  y++;
  flood_fill(cells, maxX, maxY, x, y, marked);

  x--;
  flood_fill(cells, maxX, maxY, x, y, marked);

  x--;
  flood_fill(cells, maxX, maxY, x, y, marked);

  y--;
  flood_fill(cells, maxX, maxY, x, y, marked);

  y--;
  flood_fill(cells, maxX, maxY, x, y, marked);
}

int calculate_3bv(Cell *cells, int maxX, int maxY)
{
  int _3bv = 0;
  bool *marked = calloc(maxX * maxY, sizeof(int));
  int x, y;

  for (y = 0; y < maxY; y++)
  {
    for (x = 0; x < maxX; x++)
    {
      int index = y * maxX + x;
      if (cells[index].number == 0 && cells[index].isMine == false && !marked[index])
      {
        _3bv++;
        flood_fill(cells, maxX, maxY, x, y, marked);
      }
    }
  }

  for (y = 0; y < maxY; y++)
  {
    for (x = 0; x < maxX; x++)
    {

      int index = y * maxX + x;
      if (cells[index].isMine == false && !marked[index])
      {
        _3bv++;
      }
    }
  }
  free(marked);
  return _3bv;
}