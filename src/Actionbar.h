/**
 * The left sided window displaying actions
 *
 * @author wysiwyng
 */

#ifndef ACTIONBAR_H_
#define ACTIONBAR_H_

#include <vector>
#include <unordered_set>
#include "Action.h"
#include "GameWindow.h"

class Actionbar : public GameWindow{
private:
	/**
	 * index of the currently selected action
	 */
	unsigned _active;

	/**
	 * vector of all actions
	 */
	std::vector<Action> _actions;

	/**
	 * unordered set of all actions to check for duplicates
	 */
	std::unordered_set<Action> _actions_set;

public:
	/**
	 * Constructor for Actionbar
	 * @param nr_rows the y size of this Actionbar
	 * @param nr_cols the x size of this Actionbar
	 * @param row_0 the y coordinate of the upper left corner
	 * @param col_0 the x coordinate of the upper left corner
	 */
	Actionbar(int nr_rows, int nr_cols, int row_0, int col_0);

	/**
	 * Actionbar Destructor
	 */
	~Actionbar();

	/**
	 * refreshes the Actionbar on the screen
	 */
	void refresh();

	/**
	 * adds an action to the actionbar
	 * @param act the action to add
	 */
	void add_action(Action act);

	/**
	 * creates a new action and adds it to the actionbar
	 * @param act_no the action number
	 */
	void add_action(unsigned act_no);

	/**
	 * moves the selection cursor up one line
	 */
	void move_up();

	/**
	 * moves the selection curser down one line
	 */
	void move_down();

	/**
	 * returns the selected action
	 * @returns the selected action
	 */
	Action get_action();

	/**
	 * remove the action from the actionbar
	 * @param act the action to remove
	 */
	void remove_action(Action act);

	/**
	 * removes the action with the given number from the actionbar
	 * @paramn act_no the action number to remove
	 */
	void remove_action(unsigned act_no);
};

#endif /* ACTIONBAR_H_ */
