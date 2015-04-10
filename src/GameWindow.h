#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

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

#endif /* GAMEWINDOW_H_ */
