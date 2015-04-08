/*
 * Statusbar.h
 *
 *  Created on: Mar 3, 2015
 *      Author: wysiwyng
 */

#ifndef STATUSBAR_H_
#define STATUSBAR_H_

#include <curses.h>

class Statusbar {
private:
	// Frame dimensions
	int _height, _width;
	// Frame position
	int _row, _col;

	bool _needs_refresh;

	const char* _text;

	// Pointer to an ncurses WINDOW
	WINDOW *_w;
public:
	// Get the window
	WINDOW *win();
	Statusbar(int nr_rows, int nr_cols, int row_0, int col_0);
	virtual ~Statusbar();
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
	void set_status(const char* text, bool _refresh = true);
};

#endif /* STATUSBAR_H_ */
