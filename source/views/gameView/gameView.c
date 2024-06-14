#include "gameView.h"

static Board *board;
static Difficulty currentDifficulty = DIFFICULTY_BEGINNER;
static int x = 9;
static int y = 9;
static int mines = 10;

void set_difficulty(Difficulty difficulty)
{
  currentDifficulty = difficulty;
  switch (currentDifficulty)
  {
  case DIFFICULTY_BEGINNER:
    x = 9;
    y = 9;
    mines = 10;
    break;
  case DIFFICULTY_INTERMEDIATE:
    x = 16;
    y = 16;
    mines = 40;
    break;
  case DIFFICULTY_EXPERT:
    x = 30;
    y = 16;
    mines = 99;
    break;
  }
}

void init_game_view()
{
  m3_fill(CLR_GRAY);
  board = malloc(sizeof(Board));
  new_board(board, x, y, mines, currentDifficulty);
}

void update_game_view()
{
  update_board(board);

  if (key_released(KEY_SELECT))
  {
    free_board(board);
    new_board(board, x, y, mines, currentDifficulty);
  }

  if (key_hit(KEY_START))
  {
    set_view(VIEW_MAIN_MENU);
  }
}

void close_game_view()
{
  free_board(board);
  free(board);
}