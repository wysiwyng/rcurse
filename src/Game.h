/**
 * the main game controller class
 *
 * @author wysiwyng
 */

#ifndef GAME_H_
#define GAME_H_

#include <curses.h>
#include <mutex>
#include "Hud.h"
#include "Actionbar.h"
#include "Statusbar.h"
#include "Map.h"
#include "Timer.h"
#include "TimerListener.h"

class Game : public TimerListener {
private:
	/**
	 * the height of the curses screen
	 */
	int height;

	/**
	 * the width of the curses screen
	 */
	int width;

	/**
	 * the width of the map display
	 */
	int viewport_cols;

	/**
	 * the height of the map display
	 */
	int viewport_rows;

	/**
	 * the width of the actionbar
	 */
	int actionbar_size;

	/**
	 * the Hud
	 */
	Hud hud;

	/**
	 * the Actionbar
	 */
	Actionbar act_bar;

	/**
	 * the Status bar
	 */
	Statusbar stat_bar;

	/**
	 * The Map
	 */
	Map map;

	/**
	 * the seed used for map generation
	 */
	unsigned int seed;

	/**
	 * the refresh rate in millisecends
	 */
	unsigned int tick_rate;

	/**
	 * a mutex to avoid rendering issues
	 */
	std::mutex mtx;

	/**
	 * renders everything
	 */
	void render();

public:
	/**
	 * constructor for Game
	 * @param rows the width of the curses screen
	 * @param cols the height of the curses screen
	 * @param actionbar_size the width of the actionbar
	 */
	Game(int rows, int cols, int actionbar_size);

	/**
	 * Game destructor
	 */
	virtual ~Game();

	/**
	 * displays and manages the main menu
	 * @returns 1 if exit selected, else 0
	 */
	int main_menu();

	/**
	 * displays the settings menu
	 */
	int settings();

	/**
	 * runs the main game loop
	 */
	int game_loop();

	void on_timer();
};

#endif /* GAME_H_ */
