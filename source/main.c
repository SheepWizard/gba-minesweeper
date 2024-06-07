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
	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
	m3_fill(CLR_BLUE);
	Board *b = malloc(sizeof(Board));
	new_board(b, 16, 16, 40);

	draw_selector();
	while (1)
	{
		vid_vsync();
		key_poll();
		update_board(b);

		if (key_hit(KEY_SELECT))
		{
			free_board(b);
			new_board(b, 16, 16, 40);
			reset_selector();
			draw_selector();
		}
	}

	return 0;
}