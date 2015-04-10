#include "Hud.h"
#include "Defs.h"

Hud::Hud(int nr_rows, int nr_cols, int row_0, int col_0) :
GameWindow(nr_rows, nr_cols, row_0, col_0),
_hp(0), _score(0), _xpos(0), _ypos(0),
_auto_center(false),
_seed(0)
{

}

Hud::~Hud() {

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
