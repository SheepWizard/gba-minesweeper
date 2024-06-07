#include "board.h"
#include "selector.h"

// void update_board(Board *board)
// {
//   if (board->gameOver)
//   {
//     return;
//   }
//   Selector selector = update_selector(board);
//   Cell *currentCell = &board->cells[selector.posY * board->maxY + selector.posX];
//   if (key_released(KEY_A))
//   {
//     open_cell(board, currentCell);
//     draw_cell(currentCell);
//     draw_selector();
//   }
//   if (key_hit(KEY_B))
//   {
//     flag_button_pressed(board, currentCell);
//   }
//   if (key_hit(KEY_R))
//   {
//     chord(board, currentCell);
//   }
// }
