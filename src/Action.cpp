/**
 * An action class, defines texts and numbers for rcurse menu actions
 *
 * @author wysiwyng
 */

#include "Action.h"

//ACTION_QUIT 0
//ACTION_START 1
//ACTION_UPGRADE_SWIM 2
//ACTION_UPGRADE_CLIMB 3
//ACTION_UPGRADE_ICE 4
//ACTION_HEAL 5
//ACTION_TALK 6
// ACTION_CENTER 7
// ACTION_AUTO_CENTER 8
// ACTION_DIG 9

static char const * const texts[] = {
		"==!! QUIT !!",
		"==START!",
		"--LVL UP SWIM--(20 TK)",
		"--LVL UP CLIMB-(50 TK)",
		"--LVL UP ICE---(30 TK)",
		"--HEAL---------(30 TK)",
		"--TALK",
		"==CENTER ON PLAYER",
		"==TOGGLE AUTO CENTER",
		"--DIG",
		"--SETTINGS",
		"--SEED",
		"--TICK RATE"
};

Action::Action(int _action_no) :
_no(_action_no),
_touched(false)
{

}

Action::~Action() {
	// TODO Auto-generated destructor stub
}

unsigned Action::action_no() const{
	return _no;
}

const char* Action::action_text() const{
	return texts[_no];
}
