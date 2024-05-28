// export DEVKITARM=/Users/meow/Documents/devkitpro/devkitARM
// export DEVKITPRO=/Users/meow/Documents/devkitpro
// grit cell_hidden.bmp -gb -gu16
// mgba gba-minesweeper.gba -3 -l 216
// make -f Makefile
#include "tonc.h"
#include <string.h>
#include "cell.h"
#include <stdlib.h>

int ran()
{
	return rand() % 8 + 1;
}

void nonRepeatingNumbers(int size, int max, int *out)
{
	int list[size];
	int i;
	for (i = 0; i < size; i++)
	{
		list[i] = i;
	}

	for (i = 0; i < max; i++)
	{
		int randomNumber = rand() % size;
		out[i] = list[randomNumber];
		int temp = list[randomNumber];
		list[randomNumber] = list[size - 1];
		list[size - 1] = temp;
		size--;
	}
}

void getCellNeighbours(int size, Cell *inCells, Cell *outCells)
{
	int i;
	for (i = 0; i < size; i++)
	{
	}
}

int main()
{
	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

	int maxX = 9;
	int maxY = 9;

	Cell cells[maxY][maxX];
	int x;
	int y;
	for (y = 0; y < maxY; y++)
	{
		for (x = 0; x < maxX; x++)
		{
			Cell c;
			create_cell(x, y, ran(), 0, &c);
			cells[y][x] = c;
		}
	}

	LogLevel logLevel = LOG_INFO;

	Board b;
	b.maxX = maxX;
	b.maxY = maxY;
	b.flagsPlaced = 0;
	b.gameOver = false;
	b.hitMine = false;
	b.minesCount = 10;
	b.nonMineCellsOpened = 0;
	b.cells = &cells[0][0];

	int nonRepeatingNumbersList[b.minesCount];
	nonRepeatingNumbers(b.maxX * b.maxY, b.minesCount, nonRepeatingNumbersList);

	int i;
	for (i = 0; i < b.minesCount; i++)
	{
		mgba_printf(logLevel, "%d", nonRepeatingNumbersList[i]);
		b.cells[nonRepeatingNumbersList[i]].isMine = true;
	}

	for (y = 0; y < b.maxY; y++)
	{
		for (x = 0; x < b.maxX; x++)
		{
			draw_cell(&b.cells[y * b.maxX + x]);
		}
	}

	int frameX = 0,
			frameY = 0;

	while (1)
	{
		vid_vsync();
		key_poll();
		if (key_hit(KEY_RIGHT))
		{
			frameX++;
		}
		if (key_hit(KEY_LEFT))
		{
			frameX--;
		}
		if (key_hit(KEY_UP))
		{
			frameY--;
		}
		if (key_hit(KEY_DOWN))
		{
			frameY++;
		}
		// m3_frame(frameX * cellSize, frameY * cellSize, frameX * cellSize + cellSize, frameY * cellSize + cellSize, CLR_RED);
	}

	return 0;
}