/*
 * Statusbar.cpp
 *
 *  Created on: Mar 3, 2015
 *      Author: wysiwyng
 */

#include "Statusbar.h"

Statusbar::Statusbar(int nr_rows, int nr_cols, int row_0, int col_0) {
	_w = newwin(nr_rows, nr_cols, row_0, col_0);
	_height = nr_rows;
	_width = nr_cols;
	_row = row_0;
	_col = col_0;
	_text = "";
	_needs_refresh = true;
	wattrset(_w, A_BOLD);
	box(_w,0,0);
}

Statusbar::~Statusbar() {
	delwin(_w);
}

void Statusbar::refresh() {
	if(!_needs_refresh) return;
	_needs_refresh = false;
	mvwprintw(_w, 1, 3, "%-24s", _text);
	wrefresh(_w);
}

void Statusbar::set_status(const char* text, bool _refresh) {
	if(text == _text) return;
	_needs_refresh = true;
	_text = text;
	if(_refresh) this->refresh();
}

WINDOW* Statusbar::win() {
	return _w;
}

int Statusbar::height() {
	return _height;
}

int Statusbar::width() {
	return _width;
}

int Statusbar::row() {
	return _row;
}

int Statusbar::col() {
	return _col;
}
