// export DEVKITARM=/Users/meow/Documents/devkitpro/devkitARM
// export DEVKITPRO=/Users/meow/Documents/devkitpro
// grit cell_hidden.bmp -gb -gu16
// mgba gba-minesweeper.gba -3 -l 216
// make -f Makefile
#include "tonc.h"
#include <string.h>
#include "cell.h"
#include <stdlib.h>
#include "selector.h"
#include "board.h"

LogLevel logLevel = LOG_INFO;

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

void move_mine(Board *board, Cell *cell)
{
	int y, x;
	bool moved = false;
	for (y = 0; y < board->maxY; y++)
	{
		for (x = 0; x < board->maxX; x++)
		{
			int i;
			Cell *cells = board->cells;
			Cell *c = &cells[y * board->maxY + x];
			if (c->isMine == true)
			{
				continue;
			}
			c->isMine = true;
			int neighbours[NEIGHBOUR_SIZE];
			get_cell_neighbours(board, c, neighbours);
			for (i = 0; i < NEIGHBOUR_SIZE; i++)
			{
				if (neighbours[i] == -1)
				{
					continue;
				}
				board->cells[neighbours[i]].number++;
			}
			moved = true;
			break;
		}
		if (moved)
		{
			break;
		}
	}
	int i;
	cell->isMine = false;
	int neighbours[NEIGHBOUR_SIZE];
	get_cell_neighbours(board, cell, neighbours);
	for (i = 0; i < NEIGHBOUR_SIZE; i++)
	{
		if (neighbours[i] == -1)
		{
			continue;
		}
		board->cells[neighbours[i]].number--;
	}
}

void open_multiple(Board *board, Cell *cell)
{
	Cell *stack[board->maxY * board->maxY];
	int stackTop = -1;
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
			if (neighbours[i] == -1)
			{
				continue;
			}
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

void flag_button_pressed(Board *board, Cell *cell)
{
	flag_cell(cell);
	draw_cell(cell);
	draw_selector();
	cell->isFlagged ? board->flagsPlaced++ : board->flagsPlaced--;
}

void new_game(Board *board, int maxX, int maxY, int minesCount)
{
	if (maxX * maxY <= minesCount)
	{
		minesCount = maxX * maxY - 1;
	}
	board->maxX = maxX;
	board->maxY = maxY;
	board->clicks = 0;
	board->flagsPlaced = 0;
	board->gameOver = false;
	board->minesCount = minesCount;
	board->nonMineCellsOpened = 0;

	Cell *cells = malloc(sizeof(Cell) * (maxY * maxX)); //[maxY][maxX];
	int x;
	int y;
	for (y = 0; y < maxY; y++)
	{
		for (x = 0; x < maxX; x++)
		{
			create_cell(x, y, &cells[y * maxY + x]);
		}
	}

	board->cells = cells;

	int nonRepeatingNumbersList[minesCount];
	non_repeating_numbers(maxX * maxY, minesCount, nonRepeatingNumbersList);

	int i;
	for (i = 0; i < minesCount; i++)
	{
		Cell *mineCell = &board->cells[nonRepeatingNumbersList[i]];
		mineCell->isMine = true;
		int neighbours[NEIGHBOUR_SIZE];
		get_cell_neighbours(board, mineCell, neighbours);
		int j;
		for (j = 0; j < NEIGHBOUR_SIZE; j++)
		{
			if (neighbours[j] == -1)
			{
				continue;
			}
			board->cells[neighbours[j]].number++;
		}
	}

	for (y = 0; y < maxY; y++)
	{
		for (x = 0; x < maxX; x++)
		{
			draw_cell(&board->cells[y * maxY + x]);
		}
	}
}

void free_board(Board *board)
{
	free(board->cells);
}

void end_game(Board *board, bool hasWon)
{
	int x, y;
	board->gameOver = true;
	if (hasWon)
	{
		for (y = 0; y < board->maxY; y++)
		{
			for (x = 0; x < board->maxX; x++)
			{
				Cell *c = &board->cells[y * board->maxY + x];
				if (!c->isOpen)
				{
					c->isFlagged = true;
					draw_cell(c);
				}
			}
		}
	}
	else
	{
		for (y = 0; y < board->maxY; y++)
		{
			for (x = 0; x < board->maxX; x++)
			{
				Cell *c = &board->cells[y * board->maxY + x];
				c->isOpen = true;
				draw_cell(c);
			}
		}
	}
}

void check_win(Board *board)
{
	if (board->nonMineCellsOpened < (board->maxX * board->maxY) - board->minesCount)
	{
		return;
	}
	end_game(board, true);
	mgba_printf(logLevel, "Winner");
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
			move_mine(board, cell);
			open_cell(board, cell);
			return;
		}
		// start timer
	}
	if (cell->isMine)
	{
		cell->mineHit = true;
		end_game(board, false);
		return;
	}

	board->clicks++;
	board->nonMineCellsOpened++;
	cell->isOpen = true;
	if (cell->number == 0)
	{
		open_multiple(board, cell);
	}
	check_win(board);
}

void chord(Board *board, Cell *cell)
{
	int i, flagCount = 0;
	int neighbours[NEIGHBOUR_SIZE];
	get_cell_neighbours(board, cell, neighbours);
	for (i = 0; i < NEIGHBOUR_SIZE; i++)
	{
		if (neighbours[i] == -1)
		{
			continue;
		}
		if (board->cells[neighbours[i]].isFlagged)
		{
			flagCount++;
		}
	}

	if (flagCount < cell->number)
	{
		return;
	}

	for (i = 0; i < NEIGHBOUR_SIZE; i++)
	{
		if (neighbours[i] == -1)
		{
			continue;
		}
		open_cell(board, &board->cells[neighbours[i]]);
		draw_cell(&board->cells[neighbours[i]]);
	}
}

int main()
{
	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
	m3_fill(CLR_BLUE);
	Board *b = malloc(sizeof(Board));
	new_game(b, 16, 16, 40);

	Selector oldSelector;
	oldSelector.posX = 0;
	oldSelector.posY = 0;
	draw_selector();
	while (1)
	{
		vid_vsync();
		key_poll();
		Selector selector = update_selector(b);
		if (!b->gameOver)
		{
			Cell *currentCell = &b->cells[selector.posY * b->maxY + selector.posX];
			if (key_released(KEY_A))
			{
				open_cell(b, currentCell);
				draw_cell(currentCell);
				draw_selector();
			}
			if (key_hit(KEY_B))
			{
				flag_button_pressed(b, currentCell);
			}
			if (key_hit(KEY_R))
			{
				chord(b, currentCell);
			}
		}
		if (key_hit(KEY_SELECT))
		{
			free_board(b);
			new_game(b, 16, 16, 40);
		}

		if (oldSelector.posX != selector.posX || oldSelector.posY != selector.posY)
		{
			draw_cell(&b->cells[oldSelector.posY * b->maxY + oldSelector.posX]);
			draw_selector();
			oldSelector = selector;
		}
	}

	return 0;
}