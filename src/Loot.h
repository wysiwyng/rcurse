#ifndef LOOT_H_
#define LOOT_H_

#include <unordered_set>
#include "Position.h"


class Loot {
private:
	static std::unordered_set<position> positions;
	static Loot *the_instance;
protected:
	Loot();
public:
	static Loot* instance();
	virtual ~Loot();

	static int generate_loot(int y, int x);
	static int digged(int y, int x);
};

#endif /* LOOT_H_ */
