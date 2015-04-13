/**
 * the loot generation
 *
 * @author wysiwyng
 */

#include "Loot.h"

Loot::Loot() { }

Loot::~Loot() { }

Loot* Loot::instance() {
	if(the_instance == 0) the_instance = new Loot();
	return the_instance;
}

std::unordered_set<position> Loot::positions;
Loot* Loot::the_instance = 0;

int Loot::generate_loot(int y, int x) {
	if(digged(y, x)) return 0;
	position pos = {y, x};
	positions.insert(pos);
	return 1;
}

int Loot::digged(int y, int x) {
	position pos = {y, x};
	return positions.count(pos);
}
