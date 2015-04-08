#include <curses.h>

#ifndef HUD_H
#define HUD_H

class Hud {
private:
	// Frame dimensions
	int _height, _width;
	// Frame position
	int _row, _col;


	// Pointer to an ncurses WINDOW
	WINDOW *_w;

	int _hp, _score, _max_score, _xpos, _ypos;
	bool _auto_center;
	unsigned int _seed;
	bool _needs_refresh;
public:
	// Get the window
	WINDOW *win();
	// Initialize a main window (no parent)
	Hud(int nr_rows, int nr_cols, int row_0, int col_0);

	~Hud();
	// Get the height of the window
	int height();
	// Get the width of the window
	int width();
	// Get the row (y) position of the window
	int row();
	// Get the row (y) position of the window
	int col();
	// Refresh the window
	void refresh();
	// Move a window in a new position (r, c)
	void add_points(int amount);
	void set_max_points(int amount);
	void set_pos(int x, int y);
	void set_seed(unsigned int seed);
	void set_auto_center(bool ac);
};

#endif
