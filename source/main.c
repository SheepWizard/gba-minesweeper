// export DEVKITARM=/Users/meow/Documents/devkitpro/devkitARM
// export DEVKITPRO=/Users/meow/Documents/devkitpro
// grit cell_hidden.bmp -gb -gu16
// mgba gba-minesweeper.gba -3 -l 216
// make -f Makefile
#include "tonc.h"
#include "view.h"

int main()
{
	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

	while (1)
	{
		vid_vsync();
		key_poll();
		watch_view();
	}

	return 0;
}