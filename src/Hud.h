#ifndef HUD_H
#define HUD_H

#include "GameWindow.h"

class Hud : public GameWindow{
private:

	int _hp, _score, _xpos, _ypos;
	bool _auto_center;
	unsigned int _seed;

public:
	Hud(int nr_rows, int nr_cols, int row_0, int col_0);

	~Hud();

	void refresh();
	void add_points(int amount);
	void set_pos(int x, int y);
	void set_seed(unsigned int seed);
	void set_auto_center(bool ac);
};

#endif
