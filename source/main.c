// export DEVKITARM=/Users/meow/Documents/devkitpro/devkitARM
// export DEVKITPRO=/Users/meow/Documents/devkitpro
// grit cell_hidden.bmp -gb -gu16
#include "tonc.h"
#include <string.h>
#include "cell.h"
#include <stdlib.h>

int ran()
{
	return rand() % 8 + 1;
}

int main()
{
	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

	Cell cells[8][8];
	int x;
	int y;
	for (y = 0; y < 8; y++)
	{
		for (x = 0; x < 8; x++)
		{
			Cell c;
			create_cell(x, y, ran(), 0, &c);
			cells[x][y] = c;
		}
	}

	Board b;
	b.maxX = 8;
	b.maxY = 8;
	b.flagsPlaced = 0;
	b.gameOver = false;
	b.hitMine = false;
	b.minesCount = 10;
	b.nonMineCellsOpened = 0;
	b.cells = &cells[0][0];

	for (y = 0; y < b.maxY; y++)
	{
		for (x = 0; x < b.maxX; x++)
		{
			draw_cell(&b.cells[x * b.maxX + y]);
		}
	}

	// int cellSize = 8;
	int frameX = 0,
			frameY = 0;
	// int x, y;
	// for (x = 0; x < 9; x++)
	// {
	// 	for (y = 0; y < 9; y++)
	// 	{
	// 		drawCell8(x * 8 + M3_WIDTH / 2, y * 8 + M3_HEIGHT / 2, cell_hidden_8Bitmap);
	// 	}
	// }

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