// export DEVKITARM=/Users/meow/Documents/devkitpro/devkitARM
// export DEVKITPRO=/Users/meow/Documents/devkitpro
// grit cell_hidden.bmp -gb -gu16
// mgba gba-minesweeper.gba -3 -l 216
// make -f Makefile
#include "tonc.h"
#include "highScores.h"
#include "view.h"
#include "views/titleView/titleView.h"
#include "views/gameView/gameView.h"

void update_view()
{
	switch (get_view())
	{
	case VIEW_TITLE_SCREEN:
		update_title_view();
		break;
	case VIEW_GAME:
		update_game_view();
		break;
	case VIEW_HIGH_SCORES_MENU:
	case VIEW_MAIN_MENU:
		break;
	}
}

void init_view()
{
	switch (get_view())
	{
	case VIEW_TITLE_SCREEN:
		init_title_view();
		break;
	case VIEW_GAME:
		init_game_view();
		break;
	case VIEW_HIGH_SCORES_MENU:
	case VIEW_MAIN_MENU:
		break;
	}
}

int main()
{
	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

	Views oldView = -1;

	while (1)
	{
		vid_vsync();
		key_poll();

		if (oldView != get_view())
		{
			// Probably need a close view func
			init_view();
			oldView = get_view();
		}

		update_view();
	}

	return 0;
}