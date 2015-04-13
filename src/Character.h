/**
 * A basic Character for rcurse
 *
 * @author wysiwyng
 */

#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
	/**
	 * y position
	 */
	int _row;

	/**
	 * x position
	 */
	int _col;

	/**
	 * old y position
	 */
	int _old_row;

	/**
	 * old x position
	 */
	int _old_col;

	/**
	 * character health
	 */
	int _health;

	/**
	 * set if character needs to be redrawn
	 */
	bool _redraw;

	/**
	 * is set by map if character gets out of visible area
	 */
	bool _out_of_bounds;

	/**
	 * the character's symbol
	 */
	char _symbol;
public:
	/**
	 * Constructor of character
	 * @param symbol the character's symbol
	 * @param y the initial y position
	 * @param x the initial x position
	 * @param initial_health the initial health
	 */
	Character(char symbol, int y, int x, int initial_health);

	/**
	 * sets the characters position
	 * @param y the y coordinate
	 * @param x the x coordinate
	 */
	void pos(int y, int x);

	/**
	 * moves the character
	 * @param dy the distance to move in y direction
	 * @param dx the distance to move in x direction
	 */
	void move(int dy, int dx);

	/**
	 * gets the y coordinate
	 * @returns the y coordinate
	 */
	int y();

	/**
	 * gets the x coordinate
	 * @returns the x coordinate
	 */
	int x();

	/**
	 * gets the old y coordinate
	 * @returns the old y coordinate
	 */
	int oldy();

	/**
	 * gets the old x coordinate
	 * @returns the old x coordinate
	 */
	int oldx();

	/**
	 * gets the symbol
	 * @returns the symbol
	 */
	char symbol();

	/**
	 * set if character needs to be redrawn
	 * @returns _redraw
	 */
	bool needs_redraw();

	/**
	 * resets _redraw
	 */
	void reset_redraw();

	/**
	 * sets _redraw
	 */
	void set_redraw();

	/**
	 * set if character is out of visible bounds
	 * @returns _out_of_bounds
	 */
	bool is_visible();

	/**
	 * sets _out_of_bounds
	 */
	void set_visible();

	/**
	 * resets _out_of_bounds
	 */
	void reset_visible();

	/**
	 * gets the current health
	 * @returns the current health
	 */
	int health();

	/**
	 * makes the character lose a specified amount of health
	 * @param amount the amount of health to lose
	 */
	void lose_health(int amount);

	/**
	 * adds a specified amount of health
	 * @param amount the amount of health to add
	 */
	void add_health(int amount);
};

#endif
