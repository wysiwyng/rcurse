#ifndef ACTIONBAR_H_
#define ACTIONBAR_H_

#include <vector>
#include <unordered_set>
#include "Action.h"
#include "GameWindow.h"

class Actionbar : public GameWindow{
private:
	unsigned _active;

	std::vector<Action> _actions;
	std::unordered_set<Action> _actions_set;

public:
	Actionbar(int nr_rows, int nr_cols, int row_0, int col_0);

	~Actionbar();

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
