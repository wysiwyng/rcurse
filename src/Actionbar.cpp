#include "Actionbar.h"
#include "Defs.h"

Actionbar::Actionbar(int nr_rows, int nr_cols, int row_0, int col_0) {
	_w = newwin(nr_rows, nr_cols, row_0, col_0);
	_height = nr_rows;
	_width = nr_cols;
	_row = row_0;
	_col = col_0;

	_active = 0;
	_needs_refresh = true;
	_needs_clear = true;

	wattrset(_w, A_BOLD);
	box(_w,0,0);

}

Actionbar::~Actionbar() {
	delwin(_w);
}

void Actionbar::add_action(Action act) {
	if(_actions_set.count(act)) return;
	_needs_refresh = true;
	_needs_clear = true;
	_actions_set.insert(act);
	_actions.push_back(act);
}

void Actionbar::add_action(unsigned act_no) {
	Action tmp(act_no);
	if(_actions_set.count(tmp)) return;
	_needs_refresh = true;
	_needs_clear = true;
	_actions_set.insert(tmp);
	_actions.push_back(tmp);
}

Action Actionbar::get_action() {
	return _actions[_active];
}

void Actionbar::move_down() {
	_needs_refresh = true;
	if(_active == _actions.size() - 1) _active = 0;
	else _active++;
}

void Actionbar::move_up() {
	_needs_refresh = true;
	if(_active == 0) _active = _actions.size() - 1;
	else _active--;
}

void Actionbar::remove_action(Action act) {
	if(!_actions_set.count(act)) return;
	_needs_clear = true;
	_needs_refresh = true;
	_actions_set.erase(act);
	for(unsigned i = 0; i < _actions.size(); i++) {
		if(_actions[i].action_no() == act.action_no()) _actions.erase(_actions.begin() + i);
	}
}

void Actionbar::remove_action(unsigned act_no) {
	Action tmp(act_no);
	if(!_actions_set.count(tmp)) return;
	_needs_refresh = true;
	_needs_clear = true;

	_actions_set.erase(tmp);
	for(unsigned i = 0; i < _actions.size(); i++) {
		if(_actions[i].action_no() == act_no) _actions.erase(_actions.begin() + i);
	}
	if(_active > _actions.size() - 1) _active = _actions.size() - 1;
}

void Actionbar::refresh() {
	if(!_needs_refresh) return;
	_needs_refresh = false;
	int r = 1;
	if(_needs_clear) {
		wclear(_w);
		wattron(_w, A_BOLD);
		box(_w,0,0);
		_needs_clear = false;
	}
	wattroff(_w, A_BOLD);
	for(unsigned i = 0; i < _actions.size(); i++) {
		int tmp_row = 0;

		if(_actions[i].action_no() == ACTION_QUIT) tmp_row = _height - 3;
		else if(_actions[i].action_no() == ACTION_CENTER) tmp_row = _height - 5;
		else if(_actions[i].action_no() == ACTION_AUTO_CENTER) tmp_row = _height - 4;
		else tmp_row = r++;

		if(_active == i) {
			wattron(_w, COLOR_PAIR(COLOR_HIGHLIGHT) | A_BOLD);
			mvwprintw(_w, tmp_row, 1, ">> %-24s <<", _actions[i].action_text());
			wattroff(_w, COLOR_PAIR(COLOR_HIGHLIGHT) | A_BOLD);
		}
		else {
			mvwprintw(_w, tmp_row, 1, "   %-24s   ", _actions[i].action_text());
		}
	}
	wrefresh(_w);
}

WINDOW* Actionbar::win() {
	return _w;
}

int Actionbar::height() {
	return _height;
}

int Actionbar::width() {
	return _width;
}

int Actionbar::row() {
	return _row;
}

int Actionbar::col() {
	return _col;
}
