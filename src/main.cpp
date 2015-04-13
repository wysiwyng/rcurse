/**
 * the main entrypoint for rcurse
 *
 * @author wysiwyng
 */

#include <curses.h>

#include "Game.h"
#include "Defs.h"

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
	if(!game.main_menu()) return 0;
	game.game_loop();

	return 0;
}
