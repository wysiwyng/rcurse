/*
 * Loot.h
 *
 *  Created on: Mar 14, 2015
 *      Author: wysiwyng
 */

#ifndef SRC_LOOT_H_
#define SRC_LOOT_H_

#include <unordered_set>
#include "Position.h"


class Loot {
private:
	static std::unordered_set<position> positions;
	static Loot *the_instance;
protected:
	Loot();
public:
	//Loot();
	static Loot* instance();
	virtual ~Loot();

	static int generate_loot(int y, int x);
	static int digged(int y, int x);
};

#endif /* SRC_LOOT_H_ */
