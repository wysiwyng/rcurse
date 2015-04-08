/*
 * Game.h
 *
 *  Created on: Mar 3, 2015
 *      Author: wysiwyng
 */

#ifndef GAME_H_
#define GAME_H_

#include <curses.h>

#include "Hud.h"
#include "Actionbar.h"
#include "Statusbar.h"


class Game {
private:
	int height, width, viewport_cols, viewport_rows, actionbar_size;
	Hud hud;
	Actionbar act_bar;
	Statusbar stat_bar;

public:
	Game(int rows, int cols, int actionbar_size);
	virtual ~Game();

	int main_menu();
	int game_loop();

	void do_player(char key);
	void do_menu(char key);


};

#endif /* GAME_H_ */
