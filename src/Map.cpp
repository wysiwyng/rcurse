/**
 * the map generation and display
 *
 * @author wysiwyng
 */

#include <cmath>
#include <chrono>
#include "Map.hpp"
#include "PerlinNoise.hpp"
#include "lookup.h"
#include "Loot.hpp"

namespace rcurse {
//different world generation algorithms, array seems to be the fastest
//#define DOUBLE
//#define INT
#define ARRAY

Map::Map(int _pos_y, int _pos_x, int _size_y, int _size_x, double _factor_y, double _factor_x) :
GameWindow(_size_y, _size_x, _pos_y, _pos_x),
center_x(0), center_y(0),
orig_x(0), orig_y(0),
factor_y(_factor_y), factor_x(_factor_x)
{

}

Map::Map(int _pos_y, int _pos_x, int _size_y, int _size_x, const unsigned int &seed, double _factor_y, double _factor_x) :
GameWindow(_size_y, _size_x, _pos_y, _pos_x),
center_x(0), center_y(0),
orig_x(0), orig_y(0),
factor_y(_factor_y), factor_x(_factor_x),
pn(seed)
{

}

Map::~Map() {

}

char Map::gen_from_perlin(int _ypos, int _xpos) {
	double n = pn.noise(factor_x * _xpos, factor_y * _ypos, 1.6);
#ifdef ARRAY
	int m = n * 9999;
	char temp = tiles[m];
	if(temp == CHAR_TREASURE) if(Loot::instance().digged(_ypos, _xpos)) return CHAR_GRASS;
	return temp;
#endif
#ifdef INT
	int m = n * 100;
	if (m >= 00 && m < 34) {
		return CHAR_WATER;
	}
	else if (m >= 60 && m < 80) {
		return CHAR_WALL;
	}
	else if (m >= 80 && m < 100) {
		return CHAR_ICE;
	}
	else if (m >= 37 && m < 45) {
		return CHAR_GRASS;
	}
	else if ((m >= 45 && m < 50) || (m >= 51 && m < 55)) {
		return CHAR_TALLGRASS;
	}
	else if ((m >= 34 && m < 37) || (m >= 55 && m < 60)) {
		return CHAR_EMPTY;
	}
	else if (m >= 50 && m < 51) {
		return CHAR_TREASURE;
	}

	return -1;
#endif
#ifdef DOUBLE
	if (n < 0.34) {
		return CHAR_WATER;
	}
	else if (n >= 0.60 && n < 0.8) {
		return CHAR_WALL;
	}
	else if (n >= 0.8) {
		return CHAR_ICE;
	}
	else if (n >= 0.37 && n < 0.45) {
		return CHAR_GRASS;
	}
	else if ((n >= 0.45 && n < 0.50) || (n >= 0.5001 && n < 0.55)) {
		return CHAR_TALLGRASS;
	}
	else if ((n >= 0.34 && n < 0.37) || (n >= 0.55 && n < 0.60)) {
		return CHAR_EMPTY;
	}
	else if (n >= 0.5000 && n < 0.5001) {
		return CHAR_TREASURE;
	}

	return -1;

#endif
}

int Map::get_xcenter() {return center_x;}
int Map::get_ycenter() {return center_y;}

int Map::get_xorig() {return orig_x;}
int Map::get_yorig() {return orig_y;}

void Map::init(int _row, int _col) {
	orig_x = _col;
	orig_y = _row;

	for(int i = 0; i < _height; i++) {
		for(int j = 0; j < _width; j++) {
			int chr = gen_from_perlin(i + orig_y, j + orig_x);
			set_color(_w, chr);
			mvwaddch(_w, i, j, chr);
		}
	}
	_needs_refresh = true;
}

void Map::move(int _dy, int _dx) {
	orig_x += _dx;
	orig_y += _dy;
	init(orig_y, orig_x);

}

void Map::move_fast(int _dy, int _dx) {
	if(_dy > _height || _dx > _width) {
		this->move(_dy, _dx);
		return;
	}

	this->scroll_map(_dy, _dx);

	for(int i = 0; i < std::abs(_dy); i++) {
		for(int j = 0; j < _width; j++) {
			int temp = _dy > 0 ? orig_y + _height - 1 - i : orig_y + i;
			char chr = this->gen_from_perlin(temp, orig_x + j);
			set_color(_w, chr);
			mvwaddch(_w, temp - orig_y, j, chr);
		}
	}
	for(int i = 0; i < std::abs(_dx); i++) {
		for(int j = 0; j < _height; j++) {
			int temp = _dx > 0 ? orig_x + _width - 1 - i : orig_x + i;
			int chr = this->gen_from_perlin(orig_y + j, temp);
			set_color(_w, chr);
			mvwaddch(_w, j, temp - orig_x, chr);
		}
	}
}

void Map::center(int _ypos, int _xpos) {
	int dy = _ypos - _height / 2 - orig_y;
	int dx = _xpos - _width / 2 - orig_x;
	this->move_fast(dy, dx);
}

void Map::scroll_map(int dy, int dx) {
	orig_x += dx;
	orig_y += dy;
	int _dy = dy >= 0 ? dy : -dy;
	int _dx = dx >= 0 ? dx : -dx;
	for(int i = 0; i < _height - _dy; i++) {
		for(int j = 0; j < _width - _dx; j++) {
			char chr = mvwinch(_w, dy >= 0 ? i + dy : _height - i - _dy - 1, dx >= 0 ? j + dx : _width - j - _dx - 1);
			set_color(_w, chr);
			mvwaddch(_w, dy >= 0 ? i : _height - i - 1, dx >= 0 ? j : _width - j - 1, chr);
		}
	}
	_needs_refresh = true;
}

void Map::refresh() {
	for(std::vector<Character*>::iterator it = characters.begin(); it != characters.end(); ++it) {
		if((**it).x() < orig_x || (**it).y() < orig_y || (**it).x() >= orig_x + _width || (**it).y() >= orig_y + _height) {
			(**it).reset_visible();
			(**it).set_redraw();
		}
		else
			(**it).set_visible();

		if((**it).oldx() >= orig_x && (**it).oldy() >= orig_y && (**it).oldx() < orig_x + _width && (**it).oldy() < orig_y + _height) {
			char chr = this->gen_from_perlin((**it).oldy(), (**it).oldx());
			set_color(_w, chr);
			mvwaddch(_w, (**it).oldy() - orig_y, (**it).oldx() - orig_x, chr);
			_needs_refresh = true;
		}

		if(!(**it).is_visible() && !(**it).needs_redraw()) continue;

		if((**it).x() >= orig_x && (**it).y() >= orig_y && (**it).x() < orig_x + _width && (**it).y() < orig_y + _height) {
			set_color(_w, (**it).symbol());
			mvwaddch(_w, (**it).y() - orig_y, (**it).x() - orig_x, (**it).symbol());
			_needs_refresh = true;
			(**it).reset_redraw();
		}
	}
	if(_needs_refresh) wrefresh(_w);
	_needs_refresh = false;
}

void Map::add(Character * x) {
	characters.push_back(x);
}

void Map::add(std::vector<Character>* x) {
	for(std::vector<Character>::iterator it = (*x).begin(); it != (*x).end(); it++) {
		characters.push_back(&(*it));
	}
}

char Map::target_position(int _col, int _row, bool with_characters) {
	if(with_characters) {
		for(std::vector<Character*>::iterator it = characters.begin(); it != characters.end(); it++) {
			if((**it).symbol() == CHAR_PLAYER) continue;
			if((**it).y() == _col && (**it).x() == _row) return (**it).symbol();
		}
	}
	return this->gen_from_perlin(_col, _row);
}

void Map::set_seed(unsigned int seed) {
	pn.set_seed(seed);
}
}
