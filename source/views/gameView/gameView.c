#include "views/gameView/gameView.h"

static Board *board;
static int x = 9;
static int y = 9;
static int mines = 10;

void init_game_view()
{
  m3_fill(CLR_GRAY);
  board = malloc(sizeof(Board));
  new_board(board, x, y, mines);
  draw_selector(board->maxX, board->maxY);
}

void update_game_view()
{
  update_board(board);

  if (key_hit(KEY_SELECT))
  {
    free_board(board);
    new_board(board, x, y, mines);
    reset_selector();
    draw_selector(board->maxX, board->maxY);
  }
}