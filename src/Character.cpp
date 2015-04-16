/**
 * A basic Character for rcurse
 *
 * @author wysiwyng
 */

#include "Character.h"

Character::Character(char symbol, int y, int x, int initial_health) :
_row(y), _col(x), _temp_row(y), _temp_col(x), _old_row(y), _old_col(x),
_health(initial_health),
_redraw(true), _out_of_bounds(false),
_symbol(symbol)
{

}

void Character::pos(int y, int x) {
	_redraw = true;
	_old_row = _row;
	_old_col = _col;
	_row = y;
	_col = x;
	_temp_row = y;
	_temp_col = x;
}

void Character::move(int dy, int dx) {
	//pos(_row + dy, _col + dx);
	_temp_row += dy;
	_temp_col += dx;
}

void Character::update() {
	pos(_temp_row, _temp_col);
}

int Character::y() {
	return _row;
}

int Character::x() {
	return _col;
}

int Character::oldy() {
	return _old_row;
}

int Character::oldx() {
	return _old_col;
}

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

bool Character::is_visible() {
	return _out_of_bounds;
}

void Character::reset_visible() {
	_out_of_bounds = false;
}

void Character::set_visible() {
	_out_of_bounds = true;
}

void Character::add_health(int amount) {
	_health += amount;
}

void Character::lose_health(int amount) {
	_health -= amount;
}

int Character::health() {
	return _health;
}
