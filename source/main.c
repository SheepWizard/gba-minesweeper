// export DEVKITARM=/Users/meow/Documents/devkitpro/devkitARM
// export DEVKITPRO=/Users/meow/Documents/devkitpro
// grit cell_hidden.bmp -gb -gu16
// make -f Makefile
// mgba gba-minesweeper.gba -3 -l 216
#include "tonc.h"
#include "view.h"
#include "seed.h"

// BUGS
//  bug, go expert to beginner, random cell
//  timer display not reset on new game
//  minus numbers show extra 0

int main()
{
	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

	load_seed();

	while (1)
	{
		vid_vsync();
		key_poll();
		watch_view();
	}

	return 0;
}