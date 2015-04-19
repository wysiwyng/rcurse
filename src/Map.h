/**
 * the map generation and display
 *
 * @author wysiwyng
 */

#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include "Character.h"
#include "PerlinNoise.h"
#include "Defs.h"
#include "GameWindow.h"

class Map : public GameWindow{
private:
	/**
	 * the map center x coordinate
	 */
	int center_x;

	/**
	 * the map center y coordinate
	 */
	int center_y;

	/**
	 * the map origin (left upper corner) x coordinate
	 */
	int orig_x;

	/**
	 * the map origin y coordinate
	 */
	int orig_y;

	/**
	 * the y scaling factor used for map generation
	 */
	double factor_y;

	/**
	 * the x scaling factor used for map generation
	 */
	double factor_x;

	/**
	 * a perlin noise object for map generation
	 */
	PerlinNoise pn;

	/**
	 * a vector for storing characters
	 */
	std::vector<Character*> characters;

	/**
	 * generates the symbol for a specific location
	 * @param _ypos the y coordinate
	 * @param _xpos the x coordinate
	 * @returns the symbol
	 */
	char gen_from_perlin(int _ypos, int _xpos);
public:
	/**
	 * Map constructor without seed
	 * @param _pos_y the window y coordinate
	 * @param _pos_x the window x coordinate
	 * @param _size_y the window height
	 * @param _size_x the window width
	 * @param _factor_y the y scaling factor
	 * @param _factor_x the x scaling factor
	 */
	Map(int _pos_y, int _pos_x, int _size_y, int _size_x, double _factor_y, double _factor_x);

	/**
	 * Map constructor
	 * @param _pos_y the window y coordinate
	 * @param _pos_x the window x coordinate
	 * @param _size_y the window height
	 * @param _size_x the window width
	 * @param seed the map generator seed
	 * @param _factor_y the y scaling factor
	 * @param _factor_x the x scaling factor
	 */
	Map(int _pos_y, int _pos_x, int _size_y, int _size_x, const unsigned int &seed, double _factor_y, double _factor_x);

	/**
	 * Map Destructor
	 */
	virtual ~Map();

	/**
	 * @returns the map center x coordinate
	 */
	int get_xcenter();

	/**
	 * @returns the map center y coordinate
	 */
	int get_ycenter();

	/**
	 * @returns the map origin x coordinate
	 */
	int get_xorig();

	/**
	 * @returns the map origin y coordinate
	 */
	int get_yorig();

	/**
	 * moves the map center to a character
	 * @param x the character
	 */
	void center_on_char(Character &x);

	void refresh();

	/**
	 * generates the initial map view
	 * @param _row the origin y coordinate
	 * @param _col the origin x coordinate
	 */
	void init(int _row, int _col);

	/**
	 * returns the symbol at a specified location
	 * @param _col the y coordinate
	 * @param _row the x coordinate
	 * @param with_characters returns also character's symbols
	 */
	char target_position(int _col, int _row, bool with_characters = true);

	/**
	 * moves the map origin and calls init
	 * @param _dy the y distance to move
	 * @param _dx the x distance to move
	 */
	void move(int _dy, int _dx);

	/**
	 * moves the map origin without regenerating all of the map
	 * @param _dy the y distance to move
	 * @param _dx the x distance to move
	 */
	void move_fast(int _dy, int _dx);

	/**
	 * centers the map around a position
	 * @param _ypos the y coordinate
	 * @param _xpos the x coordinate
	 */
	void center(int _ypos, int _xpos);

	/**
	 * adds a character to the character vector and the map display
	 * @param x the character
	 */
	void add(Character *x);

	/**
	 * adds a vector of characters to the character vector and the map display
	 * @param x the character vector to add
	 */
	void add(std::vector<Character>* x);

	/**
	 * scrolls the map without regenerating anything
	 * @param _dy the y distance to move
	 * @param _dx the x distance to move
	 */
	void scroll_map(int dy, int dx);

	/**
	 * sets the seed
	 * @param seed the seed to set
	 */
	void set_seed(unsigned int seed);
};

#endif /* MAP_H_ */
