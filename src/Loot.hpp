/**
 * the loot generation
 *
 * @author wysiwyng
 */

#ifndef LOOT_H_
#define LOOT_H_

#include <unordered_set>
#include <vector>
#include "Position.hpp"

namespace rcurse {

class Loot {
private:
	/**
	 * private constructor for singleton
	 */
	Loot();

	/**
	 * private copy constructor for singleton
	 */
	Loot(const Loot&);

	/**
	 * set of positions already looted
	 */
	std::unordered_set<position> positions;
public:
	/**
	 * gets the singleton instance
	 * @returns the instance
	 */
	static Loot& instance();

	/**
	 * destructor
	 */
	virtual ~Loot();

	/**
	 * generates an amount of loot at the specified location
	 * @param y the y coordinate
	 * @param x the x coordinate
	 * @returns the amount of loot
	 */
	int generate_loot(int y, int x);

	/**
	 * checks if a specified location was already looted
	 * @param y the y coordinate
	 * @param x the x coordinate
	 * @returns 1 if looted, 0 else
	 */
	int digged(int y, int x);

	/**
	 * @returns the position vector
	 */
	std::unordered_set<position>* save_positions();

	/**
	 * adds a range of positions
	 */
	void add_positions(std::unordered_set<position> pos);

	/**
	 * clears the digged loot vector
	 */
	void clear();
};
}
#endif /* LOOT_H_ */
