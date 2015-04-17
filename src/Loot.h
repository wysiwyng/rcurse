/**
 * the loot generation
 *
 * @author wysiwyng
 */

#ifndef LOOT_H_
#define LOOT_H_

#include <unordered_set>
#include "Position.h"


class Loot {
private:
	/**
	 * protected constructor for singleton
	 */
	Loot();
	Loot(const Loot&);

	/**
	 * set of positions already looted
	 */
	std::unordered_set<position> positions;

	/**
	 * a singelton instance of Loot
	 */
	//Loot *the_instance;
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
};

#endif /* LOOT_H_ */
