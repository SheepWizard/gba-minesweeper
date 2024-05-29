// export DEVKITARM=/Users/meow/Documents/devkitpro/devkitARM
// export DEVKITPRO=/Users/meow/Documents/devkitpro
// grit cell_hidden.bmp -gb -gu16
// mgba gba-minesweeper.gba -3 -l 216
// make -f Makefile
#include "tonc.h"
#include <string.h>
#include "cell.h"
#include <stdlib.h>

void non_repeating_numbers(int size, int max, int *out)
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

void get_cell_neighbours(Board *inBoard, Cell *inCell, int *outCells)
{
	int i, j, count = 0;
	for (i = -1; i < 2; i++)
	{
		for (j = -1; j < 2; j++)
		{
			int newX = i + inCell->x;
			int newY = j + inCell->y;
			if ((inCell->x != newX || inCell->y != newY) && newX > -1 && newY > -1 && newX < inBoard->maxX && newY < inBoard->maxY)
			{
				outCells[count] = newY * inBoard->maxX + newX;
				count++;
			}
		}
	}
	for (i = count; count < NEIGHBOUR_SIZE; count++)
	{
		outCells[count] = -1;
	}
}

void open_multiple(Board *board, Cell *cell)
{
	Cell *stack[board->maxY * board->maxY];
	int stackTop = -1;
	cell->isOpen = true;
	stackTop++;
	stack[stackTop] = cell;
	while (stackTop >= 0)
	{
		int i;
		Cell *poppedCell = stack[stackTop];
		stackTop--;
		int neighbours[NEIGHBOUR_SIZE];
		get_cell_neighbours(board, poppedCell, neighbours);
		for (i = 0; i < NEIGHBOUR_SIZE; i++)
		{
			Cell *neighbourCell = &board->cells[neighbours[i]];
			if (neighbourCell->isFlagged || neighbourCell->isOpen)
			{
				continue;
			}
			neighbourCell->isOpen = true;
			board->nonMineCellsOpened++;
			if (neighbourCell->number == 0)
			{
				stackTop++;
				stack[stackTop] = neighbourCell;
			}
			draw_cell(neighbourCell);
		}
	}
}

void open_cell(Board *board, Cell *cell)
{
	if (cell->isFlagged || cell->isOpen)
	{
		return;
	}

	cell->isOpen = true;
	if (board->clicks == 0)
	{
		if (cell->isMine)
		{
			// move mine
		}
		// start timer
	}
	if (cell->isMine)
	{
		// game over
		return;
	}

	board->clicks++;
	board->nonMineCellsOpened++;
	cell->isOpen = true;
	if (cell->number == 0)
	{
		open_multiple(board, cell);
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
			create_cell(x, y, 0, 0, &c);
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
	b.clicks = 0;

	int nonRepeatingNumbersList[b.minesCount];
	non_repeating_numbers(b.maxX * b.maxY, b.minesCount, nonRepeatingNumbersList);

	int i;
	for (i = 0; i < b.minesCount; i++)
	{
		b.cells[nonRepeatingNumbersList[i]].isMine = true;
		int neighbours[NEIGHBOUR_SIZE];
		get_cell_neighbours(&b, &b.cells[nonRepeatingNumbersList[i]], neighbours);
		int j;
		for (j = 0; j < NEIGHBOUR_SIZE; j++)
		{
			if (neighbours[j] == -1)
			{
				continue;
			}
			b.cells[neighbours[j]].number++;
		}
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

	int oldFrameX = frameX;
	int oldFrameY = frameY;
	m3_frame(frameX * CELL_SIZE, frameY * CELL_SIZE, frameX * CELL_SIZE + CELL_SIZE, frameY * CELL_SIZE + CELL_SIZE, CLR_RED);
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
		if (key_hit(KEY_A))
		{
			mgba_printf(logLevel, "Hit");
			open_cell(&b, &b.cells[frameY * b.maxX + frameX]);
			draw_cell(&b.cells[oldFrameY * b.maxX + oldFrameX]);
			m3_frame(frameX * CELL_SIZE, frameY * CELL_SIZE, frameX * CELL_SIZE + CELL_SIZE, frameY * CELL_SIZE + CELL_SIZE, CLR_RED);
		}
		if (frameX >= b.maxX)
		{
			frameX = 0;
		}
		if (frameX < 0)
		{
			frameX = b.maxX - 1;
		}
		if (frameY >= b.maxY)
		{
			frameY = 0;
		}
		if (frameY < 0)
		{
			frameY = b.maxY - 1;
		}

		if (oldFrameX != frameX || oldFrameY != frameY)
		{
			mgba_printf(logLevel, "Draw");
			draw_cell(&b.cells[oldFrameY * b.maxX + oldFrameX]);
			m3_frame(frameX * CELL_SIZE, frameY * CELL_SIZE, frameX * CELL_SIZE + CELL_SIZE, frameY * CELL_SIZE + CELL_SIZE, CLR_RED);
			oldFrameX = frameX;
			oldFrameY = frameY;
		}
	}

	return 0;
}