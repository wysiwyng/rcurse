/**
 * the loot generation
 *
 * @author wysiwyng
 */

#include "Loot.h"
namespace rcurse {
Loot::Loot() { }

Loot::~Loot() { }

Loot& Loot::instance() {
	static Loot _instance;
	return _instance;
}

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

std::unordered_set<position>* Loot::save_positions() {
	return &positions;
}

void Loot::add_positions(std::unordered_set<position> pos) {
	positions.insert(pos.begin(), pos.end());
}

void Loot::clear() {
	positions.clear();
}
}
