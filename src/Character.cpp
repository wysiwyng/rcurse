#include "Character.h"

// Create a character
Character::Character(char symbol, int y, int x) :
_row(y),
_col(x),
_old_row(y),
_old_col(x),
_redraw(true),
_symbol(symbol)
{

}

// Change the character position
void Character::pos(int y, int x) {
	_redraw = true;
	_old_row = _row;
	_old_col = _col;
	_row = y;
	_col = x;
}

void Character::move(int dy, int dx) {
	_redraw = true;
	_old_row = _row;
	_old_col = _col;
	_row += dy;
	_col += dx;
}

// Get character's row (y) position
int Character::y() {
	return _row;
}

// Get character's col (x) position
int Character::x() {
	return _col;
}

int Character::oldy() {
	return _old_row;
}

int Character::oldx() {
	return _old_col;
}

// Get the symbol of the character
char Character::symbol() {
	return _symbol;
}

bool Character::needs_redraw() {
	return _redraw;
}

void Character::reset_redraw() {
	_redraw = false;
}

void Character::set_redraw() {
	_redraw = true;
}
