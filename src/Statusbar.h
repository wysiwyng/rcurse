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
	int _height, _width;
	int _row, _col;

	bool _needs_refresh;

	const char* _text;

	WINDOW *_w;
public:
	WINDOW *win();
	Statusbar(int nr_rows, int nr_cols, int row_0, int col_0);
	virtual ~Statusbar();
	int height();
	int width();
	int row();
	int col();
	void refresh();
	void set_status(const char* text, bool _refresh = true);
};

#endif /* STATUSBAR_H_ */
