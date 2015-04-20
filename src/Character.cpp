/**
 * A basic Character for rcurse
 *
 * @author wysiwyng
 */

#include "Character.h"

Character::Character(const char symbol, int y, int x, int initial_health) :
_row(y), _col(x), _temp_row(y), _temp_col(x), _old_row(y), _old_col(x),
_health(initial_health),
_redraw(true), _is_visible(true),
_symbol(symbol),
_water(false), _climb(false), _ice(false)
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

int Character::tempy() {
	return _temp_row;
}

int Character::tempx() {
	return _temp_col;
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
	return _is_visible;
}

void Character::reset_visible() {
	_is_visible = false;
}

void Character::set_visible() {
	_is_visible = true;
}

/*
void Character::add_health(int amount) {
	_health += amount;
}

void Character::lose_health(int amount) {
	_health -= amount;
}
*/

void Character::set_health(int health) {
	_health = health;
}

int Character::health() {
	return _health;
}

bool Character::water() {
	return _water;
}

bool Character::climb() {
	return _climb;
}

bool Character::ice() {
	return _ice;
}

void Character::water(bool val) {
	_water = val;
}

void Character::climb(bool val) {
	_climb = val;
}

void Character::ice(bool val) {
	_ice = val;
}
