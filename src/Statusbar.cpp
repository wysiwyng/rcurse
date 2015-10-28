/**
 * a statusbar to show messages in rcurse
 *
 * @author wysiwyng
 */

#include "Statusbar.hpp"

namespace rcurse {

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
	mvwprintw(_w, 1, 3, "%-28s", _text.c_str());
	wrefresh(_w);
}

void Statusbar::set_status(std::string text, bool _refresh) {
	if(text == _text) return;
	_needs_refresh = true;
	_text = text;
	if(_refresh) this->refresh();
}

int Statusbar::read_num(std::string prompt) {
	char ch = -1;

	set_status(prompt);

	ch = getch();

	set_status("");

	while(ch != '\n' && ch != '\r') {
		if(ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9') {
			set_status(_text + ch);
		}
		else if(ch == 127 || ch == 8) {
			if(_text.length() > 0) {
				_text.pop_back();
				_needs_refresh = true;
				refresh();
			}
		}
		ch = getch();
	}

	return atoi(_text.c_str());
}
}
