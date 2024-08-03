// export DEVKITARM=/Users/meow/Documents/devkitpro/devkitARM
// export DEVKITPRO=/Users/meow/Documents/devkitpro
// grit cell_hidden.bmp -gb -gu16
// make -f Makefile
// mgba gba-minesweeper.gba -3 -l 216
#include "tonc.h"
#include "view.h"
#include "seed.h"
#include "keyHeldUtil.h"

int main()
{
	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

	load_seed();

	while (1)
	{
		vid_vsync();
		key_poll();
		key_held_update();
		watch_view();
	}

	return 0;
}