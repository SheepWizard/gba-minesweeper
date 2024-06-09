// export DEVKITARM=/Users/meow/Documents/devkitpro/devkitARM
// export DEVKITPRO=/Users/meow/Documents/devkitpro
// grit cell_hidden.bmp -gb -gu16
// mgba gba-minesweeper.gba -3 -l 216
// make -f Makefile
#include "tonc.h"
#include "selector.h"
#include "board.h"
#include "save.h"

int main()
{
	int x = 9;
	int y = 9;
	int mines = 10;
	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
	m3_fill(CLR_GRAY);
	Board *b = malloc(sizeof(Board));
	new_board(b, x, y, mines);

	// SaveData *s = malloc(sizeof(SaveData));
	// s->beginnerScores[0] = 1;
	// sram_write(s, sizeof(SaveData));

	// free(s);
	SaveData *sa = malloc(sizeof(SaveData));

	int code = sram_read(sa, sizeof(SaveData));
	if (code == E_SUCCESS)
	{
		u8 i;
		for (i = 0; i < 5; i++)
		{
			mgba_printf(LOG_INFO, "result %d", sa->beginnerScores[i]);
		}
	}

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