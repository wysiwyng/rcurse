#include <curses.h>
#include <vector>
#include <unordered_set>
#include "Action.h"

#ifndef ACTIONBAR_H_
#define ACTIONBAR_H_

class Actionbar {
private:
	int _height, _width;
	int _row, _col;

	bool _needs_refresh;
	bool _needs_clear;

	WINDOW *_w;

	unsigned _active;

	std::vector<Action> _actions;
	std::unordered_set<Action> _actions_set;

public:
	WINDOW *win();

	Actionbar(int nr_rows, int nr_cols, int row_0, int col_0);

	~Actionbar();

	int height();
	int width();
	int row();
	int col();

	void refresh();

	void add_action(Action act);

	void add_action(unsigned act_no);

	void move_up();

	void move_down();

	Action get_action();

	void remove_action(Action act);

	void remove_action(unsigned act_no);
};

#endif /* ACTIONBAR_H_ */
