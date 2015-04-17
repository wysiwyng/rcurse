/*
 * Serializer.h
 *
 *  Created on: Apr 17, 2015
 *      Author: wysiwyng
 */

#ifndef SERIALIZER_H_
#define SERIALIZER_H_

#include <vector>
#include "Character.h"
#include "Position.h"

class Serializer {
private:
	Serializer();
	Serializer(const Serializer&);

	unsigned int _seed;
	std::vector<Character> chars;
	std::vector<position> positions;

public:
	static Serializer& instance();

	void add_seed(unsigned int seed);

	void add_character(Character& chr);

	void add_score(int score);

	void add_loot_pos(int y, int x);

	void save(const char * fname);
};

#endif /* SERIALIZER_H_ */
