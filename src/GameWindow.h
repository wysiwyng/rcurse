/*
 * GameWindow.h
 *
 *  Created on: 10.04.2015
 *      Author: karsten
 */

#ifndef SRC_GAMEWINDOW_H_
#define SRC_GAMEWINDOW_H_

#include <curses.h>

class GameWindow {
protected:
	int _height, _width;
	int _row, _col;

	bool _needs_refresh;
	bool _needs_clear;

	WINDOW *_w;
public:
	GameWindow(int nr_rows, int nr_cols, int row_0, int col_0);
	virtual ~GameWindow();

	WINDOW *win();

	int height();
	int width();
	int row();
	int col();

	virtual void refresh() = 0;
};

#endif /* SRC_GAMEWINDOW_H_ */
