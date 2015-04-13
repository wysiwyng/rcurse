/**
 * a statusbar to show messages in rcurse
 *
 * @author wysiwyng
 */

#include "Statusbar.h"

Statusbar::Statusbar(int nr_rows, int nr_cols, int row_0, int col_0) :
GameWindow(nr_rows, nr_cols, row_0, col_0),
_text("")
{

}

Statusbar::~Statusbar() {

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
