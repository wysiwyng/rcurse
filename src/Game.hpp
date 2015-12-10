/**
 * the main game controller class
 *
 * @author wysiwyng
 */

#ifndef GAME_H_
#define GAME_H_

#include <curses.h>
#include <mutex>
#include "Hud.hpp"
#include "Actionbar.hpp"
#include "Statusbar.hpp"
#include "Map.hpp"
#include "Character.hpp"
#include "Timer.hpp"
#include "TimerListener.hpp"

namespace rcurse {

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
	 * the player's character
	 */
	Character player;

	/**
	 * the scaling counter for walking
	 */
	unsigned int walk_counter;
	
	/**
	 * the scaling counter for running
	 */
	unsigned int run_counter;

	struct movement_t {
		int dy;
		int dx;
		bool sprint;
	} movement, old_movement;

	game_options_t game_options;

	/**
	 * a mutex to avoid rendering issues
	 */
	std::mutex mtx;

	/**
	 * enemy vector
	 */
	std::vector<Character> enemies;

	/**
	 * renders everything
	 */
	void render();
	void do_move();

public:
	const static int RET_CONTINUE = -1;
	const static int RET_QUIT = 0;
	const static int RET_START = 1;
	const static int RET_SETTINGS = 2;
	const static int RET_LOAD = 3;

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
	 * @param from_save set to true if the game was loaded from save
	 */
	int game_loop(bool from_save);

	void on_timer();
};
}
#endif /* GAME_H_ */
