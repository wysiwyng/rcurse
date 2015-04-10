#ifndef DEFS_H_
#define DEFS_H_

#include <curses.h>

#define CHAR_PLAYER '@'
#define CHAR_ENEMY 'E'

#define CHAR_GRASS ','
#define CHAR_TALLGRASS ';'
#define CHAR_WATER '~'
#define CHAR_WALL '#'
#define CHAR_ICE '+'
#define CHAR_TREASURE '.'
#define CHAR_LOOTED '_'
#define CHAR_EMPTY ' '

#define COLOR_PLAYER 1
#define COLOR_ENEMY 2
#define COLOR_GRASS 3
#define COLOR_WATER 4
#define COLOR_WALL 5
#define COLOR_ICE 6
#define COLOR_TREASURE 7
#define COLOR_STD 0
#define COLOR_HIGHLIGHT 7

#define COLOR_HUD 6

namespace Defs {

	void init_colors();

	short get_color(char symbol);
	void set_color(WINDOW *w, char chr);
}

#endif /* DEFS_H_ */
