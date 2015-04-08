#include <curses.h>
#include <vector>
#include <unordered_set>
#include "Action.h"

#ifndef ACTIONBAR_H_
#define ACTIONBAR_H_

class Actionbar {
private:
	// Frame dimensions
	int _height, _width;
	// Frame position
	int _row, _col;

	bool _needs_refresh;
	bool _needs_clear;

	// Pointer to an ncurses WINDOW
	WINDOW *_w;

	unsigned _active;

	std::vector<Action> _actions;
	std::unordered_set<Action> _actions_set;

public:
	// Get the window
	WINDOW *win();
	// Initialize a main window (no parent)
	Actionbar(int nr_rows, int nr_cols, int row_0, int col_0);

	~Actionbar();
	// Get the height of the window
	int height();
	// Get the width of the window
	int width();
	// Get the row (y) position of the window
	int row();
	// Get the row (y) position of the window
	int col();
	// Refresh the window
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
