/**
 * A HUD for rcurse, displays score health etc
 *
 * @author wysiwyng
 */

#ifndef HUD_H
#define HUD_H

#include "GameWindow.h"

class Hud : public GameWindow{
private:
	/**
	 * the health
	 */
	int _hp;

	/**
	 * the current score
	 */
	int _score;

	/**
	 * the player's x coordinate
	 */
	int _xpos;

	/**
	 * the player's y coordinate
	 */
	int _ypos;

	/**
	 * map auto center variable
	 */
	bool _auto_center;

	/**
	 * the map seed
	 */
	unsigned int _seed;

	/**
	 * the tick rate (fps)
	 */
	unsigned int _fps;

public:
	/**
	 * Constructor for Hud
	 * @param nr_rows the y size of this Hud
	 * @param nr_cols the x size of this Hud
	 * @param row_0 the y coordinate of the upper left corner
	 * @param col_0 the x coordinate of the upper left corner
	 */
	Hud(int nr_rows, int nr_cols, int row_0, int col_0);

	/**
	 * Destructor
	 */
	~Hud();

	void refresh();

	/**
	 * adds a specified amount of points
	 * @param amount the amount of points to add
	 */
	void add_points(int amount);

	/**
	 * sets the position of the player
	 * @param x the x coordinate
	 * @param y the y coordinate
	 */
	void set_pos(int x, int y);

	/**
	 * sets the seed
	 * @param seed the seed
	 */
	void set_seed(unsigned int seed);

	/**
	 * sets the map auto center display
	 * @param ac sets auto center
	 */
	void set_auto_center(bool ac);

	/**
	 * sets the hp display
	 * @param hp the health to display
	 */
	void set_hp(int hp);

	/**
	 * sets the fps
	 * @param fps the current fps
	 */
	void set_fps(int fps);
};

#endif
