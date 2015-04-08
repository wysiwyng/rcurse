#include <curses.h>

#ifndef HUD_H
#define HUD_H

class Hud {
private:
	int _height, _width;
	int _row, _col;

	WINDOW *_w;

	int _hp, _score, _max_score, _xpos, _ypos;
	bool _auto_center;
	unsigned int _seed;
	bool _needs_refresh;
public:
	WINDOW *win();
	Hud(int nr_rows, int nr_cols, int row_0, int col_0);

	~Hud();
	int height();
	int width();
	int row();
	int col();
	void refresh();
	void add_points(int amount);
	void set_max_points(int amount);
	void set_pos(int x, int y);
	void set_seed(unsigned int seed);
	void set_auto_center(bool ac);
};

#endif
