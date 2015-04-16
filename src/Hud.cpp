/**
 * A HUD for rcurse, displays score health etc
 *
 * @author wysiwyng
 */

#include "Hud.h"
#include "Defs.h"

Hud::Hud(int nr_rows, int nr_cols, int row_0, int col_0) :
GameWindow(nr_rows, nr_cols, row_0, col_0),
_hp(0), _score(0), _xpos(0), _ypos(0),
_auto_center(false),
_seed(0),
_fps(0)
{

}

Hud::~Hud() {

}

void Hud::set_seed(unsigned int seed) {
	_needs_refresh = true;
	_seed = seed;
}

void Hud::set_pos(int x, int y) {
	if(x == _xpos && y == _ypos) return;
	_needs_refresh = true;
	_xpos = x;
	_ypos = y;
}

void Hud::refresh() {
	if(!_needs_refresh) return;
	_needs_refresh = false;
	mvwprintw(_w, 1, 2, "[HP:%03d] [PTS:%04d] [POS:%04dx%04dy] [%4s] [FPS:%03d] [SEED:%u]", _hp, _score, _xpos, _ypos, _auto_center ? "AUTO" : "MAN", _fps, _seed);
	wrefresh(_w);
}

void Hud::set_points(int amount){
	_needs_refresh = true;
	_score = amount;
}

void Hud::set_auto_center(bool ac) {
	_needs_refresh = true;
	_auto_center = ac;
}

void Hud::set_hp(int hp){
	_needs_refresh = true;
	_hp = hp;
}

void Hud::set_fps(int fps) {
	_needs_refresh = true;
	_fps = fps;
}
