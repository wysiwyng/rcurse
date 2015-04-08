/*
 * Loot.cpp
 *
 *  Created on: Mar 14, 2015
 *      Author: wysiwyng
 */

#include "Loot.h"

Loot::Loot() {
	// TODO Auto-generated constructor stub

}

Loot::~Loot() {
	// TODO Auto-generated destructor stub
}

Loot* Loot::instance() {
	if(the_instance == 0) the_instance = new Loot();
	return the_instance;
}

std::unordered_set<position> Loot::positions;
Loot* Loot::the_instance = 0;

int Loot::generate_loot(int y, int x) {
	if(digged(y, x)) return 0;
	positions.insert({y, x});
	return 1;
}

int Loot::digged(int y, int x) {
	return positions.count({y, x});
}
