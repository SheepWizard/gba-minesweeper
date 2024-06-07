// export DEVKITARM=/Users/meow/Documents/devkitpro/devkitARM
// export DEVKITPRO=/Users/meow/Documents/devkitpro
// grit cell_hidden.bmp -gb -gu16
// mgba gba-minesweeper.gba -3 -l 216
// make -f Makefile
#include "tonc.h"
#include "selector.h"
#include "board.h"

LogLevel logLevel = LOG_INFO;

int main()
{
	int x = 16;
	int y = 16;
	int mines = 40;
	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
	m3_fill(CLR_ORANGE);
	Board *b = malloc(sizeof(Board));
	new_board(b, x, y, mines);

	draw_selector(b->maxX, b->maxY);
	while (1)
	{
		vid_vsync();
		key_poll();
		update_board(b);

		if (key_hit(KEY_SELECT))
		{
			free_board(b);
			new_board(b, x, y, mines);
			reset_selector();
			draw_selector(b->maxX, b->maxY);
		}
	}

	return 0;
}