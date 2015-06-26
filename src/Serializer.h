/*
 * Serializer.h
 * a serializer class to save and load game data to xml
 *  Created on: Apr 17, 2015
 *  @author: wysiwyng
 */

#ifndef SERIALIZER_H_
#define SERIALIZER_H_

#include <vector>
#include <unordered_set>
#include <pugixml.hpp>
#include "Character.h"
#include "Position.h"

namespace rcurse {

class Serializer {
private:
	/**
	 * private constructor for singleton
	 */
	Serializer();

	/**
	 * private copy constructor
	 */
	Serializer(const Serializer&);

	/**
	 * the character vector
	 */
	std::vector<Character> _chars;

	/**
	 * a set of loot positions
	 */
	std::unordered_set<position> _positions;

	/**
	 * the main player character
	 */
	Character _player;

	/**
	 * the pugixml xml document
	 */
	pugi::xml_document _doc;

	/**
	 * the map seed
	 */
	unsigned int _seed;

	/**
	 * the game score
	 */
	int _score;

public:
	/**
	 * gets or creates the singleton instance
	 */
	static Serializer& instance();

	/**
	 * adds a seed to the serializer
	 * @param seed the seed to add
	 */
	void add_seed(unsigned int seed);

	/**
	 * adds a character to the character vector, use for npcs
	 * @param chr the character to add
	 */
	void add_character(Character& chr);

	/**
	 * adds a vector of characters to the character vector, use for npcs
	 * @param chrs the character vector to add
	 */
	void add_character(std::vector<Character>const * const chrs);

	/**
	 * adds the player character
	 * @param player the player character
	 */
	void add_player(Character player);

	/**
	 * clears the character vector and resets the player character
	 */
	void clear_characters();

	/**
	 * adds a score value
	 * @param score the score
	 */
	void add_score(int score);

	/**
	 * adds a distinctive loot position
	 * @param y the y coordinate
	 * @param x the x coordinate
	 */
	void add_loot_pos(int y, int x);

	/**
	 * adds a set of loot positions
	 * @param pos the set of loot positions
	 */
	void add_loot_pos(std::unordered_set<position>const * const pos);

	/**
	 * deletes all loot positions from the storage set
	 */
	void clear_lot_pos();

	/**
	 * saves the gamedata to filesystem
	 */
	int save();

	/**
	 * clears everything
	 */
	void clear();

	/**
	 * reads the gamedate from filesystem
	 * @param fname the filename to read from
	 * @returns success of reading
	 */
	bool read(char* fname);

	/**
	 * @returns the game seed
	 */
	unsigned int seed();

	/**
	 * @returns the score
	 */
	int score();

	/**
	 * @returns the main character
	 */
	Character player();

	/**
	 * @returns the npc character vector
	 */
	std::vector<Character> char_vec();

	/**
	 * @returns the loot positions set
	 */
	std::unordered_set<position> pos_set();
};
}
#endif /* SERIALIZER_H_ */
