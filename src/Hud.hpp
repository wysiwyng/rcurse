/**
 * A HUD for rcurse, displays score health etc
 *
 * @author wysiwyng
 */

#ifndef HUD_H
#define HUD_H

#include "GameWindow.hpp"
#include "Defs.hpp"
#include "Character.hpp"
namespace rcurse {
class Hud : public GameWindow{
private:
	game_options_t* _game_options;
	Character* _player;

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

	void add_player(Character * player);
	void add_game_options(game_options_t * game_options);

	void refresh();
};
}
#endif
