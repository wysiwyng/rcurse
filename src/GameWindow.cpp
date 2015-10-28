/**
 * An abstract curses window to use in rcurse
 *
 * @author wysiwyng
 */

#include "GameWindow.hpp"
namespace rcurse {
GameWindow::GameWindow(int nr_rows, int nr_cols, int row_0, int col_0) :
_height(nr_rows),
_width(nr_cols),
_row(row_0),
_col(col_0),
_needs_refresh(true),
_needs_clear(true),
_w(newwin(_height, _width, _row, _col))
{
	wattrset(_w, A_BOLD);
	box(_w, 0, 0);
}

GameWindow::~GameWindow() {
	delwin(_w);
}

int GameWindow::height(){
	return _height;
}

int GameWindow::width(){
	return _width;
}

int GameWindow::row(){
	return _row;
}

int GameWindow::col(){
	return _col;
}
}
