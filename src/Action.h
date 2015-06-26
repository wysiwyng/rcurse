/**
 * An action class, defines texts and numbers for rcurse menu actions
 *
 * @author wysiwyng
 */

#ifndef ACTION_H_
#define ACTION_H_



#include <functional>
namespace rcurse {
/**
 * Action class, used in the rcurse menu
 */
class Action {
private:
	///the action number
	unsigned _no;

	///action drawn on screen?
	bool _touched;

	//const char* _text;
	static const char * const texts[];
public:
	const static int ACTION_QUIT = 0;
	const static int ACTION_START = 1;
	const static int ACTION_UPGRADE_SWIM = 2;
	const static int ACTION_UPGRADE_CLIMB = 3;
	const static int ACTION_UPGRADE_ICE = 4;
	const static int ACTION_HEAL = 5;
	const static int ACTION_TALK = 6;
	const static int ACTION_CENTER = 7;
	const static int ACTION_AUTO_CENTER = 8;
	const static int ACTION_DIG = 9;
	const static int ACTION_SETTINGS = 10;
	const static int ACTION_SEED = 11;
	const static int ACTION_TICKRATE = 12;
	const static int ACTION_SAVE = 13;
	const static int ACTION_LOAD = 14;
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
}
namespace std {
template<>
class hash<rcurse::Action> {
public:
	size_t operator()(const rcurse::Action &action) const {
		return hash<unsigned>()(action.action_no());
	}
};
}

#endif /* ACTION_H_ */
