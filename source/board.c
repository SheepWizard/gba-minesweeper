#include "board.h"

static Selector oldSelector;

static void non_repeating_numbers(int size, const int max, int *out)
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

static void get_cell_neighbours(const Board *inBoard, const Cell *inCell, int *outCells)
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

static void move_mine(Board *board, Cell *cell)
{
  int y, x;
  bool moved = false;
  for (y = 0; y < board->maxY; y++)
  {
    for (x = 0; x < board->maxX; x++)
    {
      int i;
      Cell *cells = board->cells;
      Cell *c = &cells[y * board->maxX + x];
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

static void open_multiple(Board *board, Cell *cell)
{
  Cell *stack[board->maxX * board->maxY];
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
      draw_cell(neighbourCell, board->maxX, board->maxY);
    }
  }
}

static void flag_button_pressed(Board *board, Cell *cell)
{
  flag_cell(cell);
  draw_cell(cell, board->maxX, board->maxY);
  draw_selector(board->maxX, board->maxY);
  cell->isFlagged ? board->flagsPlaced++ : board->flagsPlaced--;
  draw_dot_display(board->minesCount - board->flagsPlaced, DOT_DISPLAY_SIDE_LEFT);
}

void new_board(Board *board, const int maxX, const int maxY, int minesCount, Difficulty difficulty)
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
  board->time = 0;
  board->difficulty = difficulty;

  Cell *cells = malloc(sizeof(Cell) * (maxY * maxX));
  int x;
  int y;
  for (y = 0; y < maxY; y++)
  {
    for (x = 0; x < maxX; x++)
    {
      create_cell(x, y, &cells[y * maxX + x]);
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
      draw_cell(&board->cells[y * maxX + x], board->maxX, board->maxY);
    }
  }
  stop_timer();
  reset_selector();
  draw_selector(board->maxX, board->maxY);
  draw_smile(SMILE_PLAY);
  draw_dot_display(board->minesCount - board->flagsPlaced, DOT_DISPLAY_SIDE_LEFT);
  draw_dot_display(0, DOT_DISPLAY_SIDE_RIGHT);
}

void free_board(Board *board)
{
  free(board->cells);
}

static void end_game(Board *board, const bool hasWon)
{
  int x, y;
  board->gameOver = true;
  stop_timer();
  if (hasWon)
  {
    for (y = 0; y < board->maxY; y++)
    {
      for (x = 0; x < board->maxX; x++)
      {
        Cell *c = &board->cells[y * board->maxX + x];
        if (!c->isOpen)
        {
          c->isFlagged = true;
          draw_cell(c, board->maxX, board->maxY);
        }
      }
    }
    draw_dot_display(board->minesCount - board->flagsPlaced, DOT_DISPLAY_SIDE_LEFT);
    draw_smile(SMILE_WIN);
    save_score(board->difficulty, (u8)board->time);
  }
  else
  {
    for (y = 0; y < board->maxY; y++)
    {
      for (x = 0; x < board->maxX; x++)
      {
        Cell *c = &board->cells[y * board->maxX + x];
        c->isOpen = true;
        draw_cell(c, board->maxX, board->maxY);
      }
    }
    draw_smile(SMILE_DEAD);
  }
}

static void check_win(Board *board)
{
  if (board->nonMineCellsOpened < (board->maxX * board->maxY) - board->minesCount)
  {
    return;
  }
  end_game(board, true);
}

static void open_cell(Board *board, Cell *cell)
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
    }
    start_timer();
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

static void chord_hover(Board *board, Cell *cell)
{
  int i;
  int neighbours[NEIGHBOUR_SIZE];
  get_cell_neighbours(board, cell, neighbours);
  for (i = 0; i < NEIGHBOUR_SIZE; i++)
  {
    if (neighbours[i] == -1 || board->cells[neighbours[i]].hovered)
    {
      continue;
    }
    board->cells[neighbours[i]].hovered = true;
    draw_cell(&board->cells[neighbours[i]], board->maxX, board->maxY);
  }
}

static void chord(Board *board, Cell *cell)
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
    draw_cell(&board->cells[neighbours[i]], board->maxX, board->maxY);
  }
}

static void clear_hovered_cells(Board *board)
{
  int i;
  int max = board->maxX * board->maxY;
  for (i = 0; i < max; i++)
  {
    if (!board->cells[i].hovered)
    {
      continue;
    }
    board->cells[i].hovered = false;
    draw_cell(&board->cells[i], board->maxX, board->maxY);
  }
}

static void update_timer(Board *board)
{
  int currentTime = read_timer();
  if (currentTime != board->time)
  {
    board->time = currentTime;
    draw_dot_display(currentTime, DOT_DISPLAY_SIDE_RIGHT);
  }
}

void update_board(Board *board)
{
  if (board->gameOver)
  {
    return;
  }
  Selector selector = update_selector(board->maxX, board->maxY);
  Cell *currentCell = &board->cells[selector.posY * board->maxX + selector.posX];

  if (oldSelector.posX != selector.posX || oldSelector.posY != selector.posY)
  {
    clear_hovered_cells(board);
    draw_cell(&board->cells[oldSelector.posY * board->maxX + oldSelector.posX], board->maxX, board->maxY);
    draw_selector(board->maxX, board->maxY);
    oldSelector = selector;
  }
  if (key_is_down(KEY_A) && !currentCell->isOpen && !currentCell->hovered)
  {
    draw_smile(SMILE_OFACE);
    currentCell->hovered = true;
    draw_cell(currentCell, board->maxX, board->maxY);
    draw_selector(board->maxX, board->maxY);
  }
  if (key_released(KEY_A))
  {
    draw_smile(SMILE_PLAY);
    open_cell(board, currentCell);
    draw_cell(currentCell, board->maxX, board->maxY);
    draw_selector(board->maxX, board->maxY);
  }
  if (key_hit(KEY_B))
  {
    flag_button_pressed(board, currentCell);
  }
  if (key_is_down(KEY_R) && currentCell->isOpen && currentCell->number != 0)
  {
    chord_hover(board, currentCell);
    draw_selector(board->maxX, board->maxY);
  }
  if (key_released(KEY_R))
  {
    clear_hovered_cells(board);
    if (currentCell->isOpen && currentCell->number != 0)
    {
      chord(board, currentCell);
    }
  }
  // Time not updating properly on new game
  update_timer(board);
}
