/*
 * Serializer.h
 *
 *  Created on: Apr 17, 2015
 *      Author: wysiwyng
 */

#ifndef SERIALIZER_H_
#define SERIALIZER_H_

#include <vector>
#include <unordered_set>
#include <pugixml.hpp>
#include "Character.h"
#include "Position.h"

class Serializer {
private:
	Serializer();
	Serializer(const Serializer&);

	std::vector<Character> _chars;
	std::unordered_set<position> _positions;

	pugi::xml_document _doc;

	unsigned int _seed;

	int _score;

public:
	static Serializer& instance();

	void add_seed(unsigned int seed);

	void add_character(Character& chr);

	void add_character(std::vector<Character>const * const chrs);

	void clear_characters();

	void add_score(int score);

	void add_loot_pos(int y, int x);

	void add_loot_pos(std::unordered_set<position>const * const pos);

	void clear_lot_pos();

	void save();

	void clear();

	void read(char* fname);

	unsigned int seed();

	int score();

	std::vector<Character> char_vec();

	std::unordered_set<position> pos_set();
};

#endif /* SERIALIZER_H_ */
