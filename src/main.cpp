/**
 * the main entrypoint for rcurse
 *
 * @author wysiwyng
 */

#include <curses.h>

#include "Game.h"
#include "Defs.h"

/**
 * main entrypoint
 */
int main() {
	initscr();
	clear();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);

	int _height, _width;
	getmaxyx(stdscr, _height, _width);
	start_color();
	Defs::init_colors();

	refresh();

	Game game(_height, _width, 30);

	int ret = Game::RET_CONTINUE;
	while (1) {
		ret = game.main_menu();
		if(ret == Game::RET_SETTINGS) game.settings();
		else if(ret == Game::RET_START) game.game_loop(false);
		else if(ret == Game::RET_LOAD) game.game_loop(true);
		else if(ret == Game::RET_QUIT) return 0;
	}

	return 0;
}
