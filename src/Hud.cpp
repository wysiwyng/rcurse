/**
 * A HUD for rcurse, displays score health etc
 *
 * @author wysiwyng
 */

#include "Hud.hpp"
#include "Defs.hpp"
namespace rcurse {
Hud::Hud(int nr_rows, int nr_cols, int row_0, int col_0) :
GameWindow(nr_rows, nr_cols, row_0, col_0),
_game_options(0),
_player(0)
{

}

Hud::~Hud() {

}

void Hud::add_game_options(game_options_t * game_options) {
	_game_options = game_options;
}

void Hud::add_player(Character * player) {
	_player = player;
}

void Hud::refresh() {
	if(!_needs_refresh) return;
	_needs_refresh = false;
	mvwprintw(_w, 1, 2, "[HP:%03d] [PTS:%04d] [%04dx%04dy] [%4s] [FPS:%03d] [SEED:%10u], [%1s%1s%1s]", _player->health(), _game_options->score, _player->x(), _player->y(), _game_options->auto_center ? "AUTO" : "MAN", 1000 / _game_options->tick_rate, _game_options->seed, _player->water() ? "S" : " ", _player->climb() ? "C" : " ", _player->ice() ? "I" : " ");
	wrefresh(_w);
}

}
