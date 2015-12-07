/**
 * Global definitions in a seperate namespace
 *
 * @author wysiwyng
 */


#ifndef DEFS_H_
#define DEFS_H_

#include <curses.h>



namespace rcurse {
	const static char CHAR_PLAYER = '@';
	const static char CHAR_ENEMY = 'E';

	const static char CHAR_GRASS = ',';
	const static char CHAR_TALLGRASS = ';';
	const static char CHAR_WATER = '~';
	const static char CHAR_WALL = '#';
	const static char CHAR_ICE = '+';
	const static char CHAR_TREASURE = '.';
	const static char CHAR_LOOTED = '_';
	const static char CHAR_EMPTY = ' ';
	const static char CHAR_TREE = 'T';
	const static char CHAR_FLOWER = '*';

	const static int COLOR_PLAYER = 1;
	const static int COLOR_ENEMY = 2;
	const static int COLOR_GRASS = 3;
	const static int COLOR_WATER = 4;
	const static int COLOR_WALL = 5;
	const static int COLOR_ICE = 6;
	const static int COLOR_TREASURE = 7;
	const static int COLOR_STD = 0;
	const static int COLOR_HIGHLIGHT = 7;
	const static int COLOR_FLOWER = 8;

	const static int COLOR_HUD = 6;

	struct game_options_t {
		int score;
		bool auto_center;
		unsigned int seed;
		unsigned int tick_rate;
	};
	/**
	 * initializes color pairs
	 */
	void init_colors();

	/**
	 * gets the color pair code specific for a symbol
	 * @param symbol the symbol
	 * @returns the color pair code
	 */
	short get_color(char symbol);

	/**
	 * sets the color in the specified curses window to the specified character color
	 * @param w the window
	 * @param chr the character
	 */
	void set_color(WINDOW *w, char chr);
}

#endif /* DEFS_H_ */
