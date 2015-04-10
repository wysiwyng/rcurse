/*
 * Map.h
 *
 *  Created on: Mar 4, 2015
 *      Author: wysiwyng
 */

#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include "Character.h"
#include "PerlinNoise.h"
#include "Defs.h"
#include "GameWindow.h"

class Map : public GameWindow{
private:
	int old_col, old_row, old_char;

	int center_x, center_y;
	int orig_x, orig_y;

	double factor_y, factor_x;
	PerlinNoise pn;

	std::vector<Character*> characters;
	char gen_from_perlin(int _ypos, int _xpos);
public:
	Map(int _pos_y, int _pos_x, int _size_y, int _size_x, const unsigned int &seed, double _factor_y, double _factor_x);
	virtual ~Map();

	int get_old_col();
	int get_old_row();
	int get_old_char();

	int get_xcenter();
	int get_ycenter();

	int get_xorig();
	int get_yorig();

	void center_on_char(Character &x);

	void refresh();

	void init(int _row, int _col);

	char target_position(int _col, int _row);
	void move(int _dy, int _dx);
	void move_fast(int _dy, int _dx);
	void center(int _ypos, int _xpos);

	void add(Character *x);
	void update(Character &x);

	void scroll_x(int count);
	void scroll_right();
	void scroll_left();
	void scroll_y(int count);
	void scroll_down();
	void scroll_up();

	void scroll_map(int y, int x);
};

#endif /* MAP_H_ */
