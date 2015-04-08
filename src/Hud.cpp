#include "Hud.h"
#include "Defs.h"

// Initialize a main window (no parent)
Hud::Hud(int nr_rows, int nr_cols, int row_0, int col_0) {
	_w = newwin(nr_rows, nr_cols, row_0, col_0);
	_height = nr_rows;
	_width = nr_cols;
	_row = row_0;
	_col = col_0;
	_max_score = 0;
	wattrset(_w, A_BOLD);
	box(_w,0,0);
	_hp = 100;
	_score = 0;
	_xpos = 0;
	_ypos = 0;
	_auto_center = false;
	_seed = 0;
	_needs_refresh = true;
}

Hud::~Hud() {
	delwin(_w);
}

void Hud::set_seed(unsigned int seed) {
	_needs_refresh = true;
	_seed = seed;
}

void Hud::set_pos(int x, int y) {
	_needs_refresh = true;
	_xpos = x;
	_ypos = y;
}

void Hud::set_max_points(int amount)
{
	_needs_refresh = true;
	_max_score = amount;
}

// Refresh the window
void Hud::refresh() {
	if(!_needs_refresh) return;
	_needs_refresh = false;
	mvwprintw(_w, 1, 2, "[HP:%03d]", _hp);
	mvwprintw(_w, 1, 11, "[TK:%04d]", _score);
	mvwprintw(_w, 1, 21, "[POS:%04dx%04dy]", _xpos, _ypos);
	mvwprintw(_w, 1, 38, "[SEED:%u]", _seed);
	mvwprintw(_w, 1, 63, "[%4s]", _auto_center ? "AUTO" : "MAN");
	wrefresh(_w);
}

void Hud::add_points(int amount){
	_needs_refresh = true;
	_score += amount;
}

void Hud::set_auto_center(bool ac) {
	_auto_center = ac;
}

// Get the window
WINDOW* Hud::win() {
	return _w;
}

// Get the height of the window
int Hud::height() {
	return _height;
}

// Get the width of the window
int Hud::width() {
	return _width;
}

// Get the row (y) position of the window
int Hud::row() {
	return _row;
}

// Get the row (y) position of the window
int Hud::col() {
	return _col;
}
