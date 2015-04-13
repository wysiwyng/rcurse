/**
 * An action class, defines texts and numbers for rcurse menu actions
 *
 * @author wysiwyng
 */

#ifndef ACTION_H_
#define ACTION_H_

#define ACTION_QUIT 0
#define ACTION_START 1
#define ACTION_UPGRADE_SWIM 2
#define ACTION_UPGRADE_CLIMB 3
#define ACTION_UPGRADE_ICE 4
#define ACTION_HEAL 5
#define ACTION_TALK 6
#define ACTION_CENTER 7
#define ACTION_AUTO_CENTER 8
#define ACTION_DIG 9

#include <functional>

class Action {
private:
	/**
	 * the action number
	 */
	unsigned _no;

	/**
	 * action drawn on screen?
	 */
	bool _touched;

	//const char* _text;

public:
	/**
	 * Constructor for Action
	 * @param _action_no the action index
	 */
	Action(int _action_no);

	/**
	 * Action destructor
	 */
	virtual ~Action();

	/**
	 * getter for action_no
	 * @returns _action_no
	 */
	unsigned action_no() const;

	/**
	 * gets the actual text of this action object
	 * @returns action text
	 */
	const char* action_text() const;

	/**
	 * equals operator for usage in data structures
	 */
	bool operator==(const Action &other) const {
		return _no == other._no;
	}
};

namespace std {
template<>
class hash<Action> {
public:
	size_t operator()(const Action &action) const {
		return hash<unsigned>()(action.action_no());
	}
};
}

#endif /* ACTION_H_ */
