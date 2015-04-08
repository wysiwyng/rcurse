/*
 * Game.cpp
 *
 *  Created on: Mar 3, 2015
 *      Author: wysiwyng
 */

#include "Game.h"
#include "Character.h"
#include "Defs.h"
#include "Map.h"
#include "Loot.h"
#include <chrono>
#include <iostream>

Game::Game(int rows, int cols, int _actionbar_size) :
hud(3, cols, 0, 0),
act_bar(rows - 6, _actionbar_size + 2, 3, 0),
stat_bar(3, _actionbar_size + 2, rows - 3, 0){
	stat_bar.set_status("Early init");
	height = rows;
	width = cols;
	actionbar_size = _actionbar_size;
	viewport_rows = height - 5;
	viewport_cols = width - actionbar_size - 4;

	act_bar.add_action(ACTION_START);
	act_bar.add_action(ACTION_QUIT);

	WINDOW *viewport_border = newwin(viewport_rows + 2, viewport_cols + 2, 3, actionbar_size + 2);
	wattrset(viewport_border, A_BOLD);
	box(viewport_border, 0, 0);

	//refresh();
	wrefresh(viewport_border);
	hud.refresh();
	act_bar.refresh();
	stat_bar.set_status("Idle");
}

Game::~Game() {
	endwin();
}

int Game::main_menu() {
	stat_bar.set_status("Main Menu");
	int ch = 0;
	int act = -1;

	while(1) {
		ch = getch();
		switch(ch) {
		case KEY_UP:
			act_bar.move_up();
			break;
		case KEY_DOWN:
			act_bar.move_down();
			break;
		case '\n': case ' ':
			act = act_bar.get_action().action_no();
			break;
		}

		if (act == ACTION_QUIT) return 0;
		else if(act == ACTION_START) break;

		act_bar.refresh();
	}

	act_bar.remove_action(ACTION_START);
	act_bar.remove_action(ACTION_QUIT);

	act_bar.add_action(ACTION_CENTER);
	act_bar.add_action(ACTION_AUTO_CENTER);
	act_bar.add_action(ACTION_QUIT);

	for(int i = 2; i <= 6; i++) act_bar.add_action(i);

	act_bar.refresh();
	return 1;
}

int Game::game_loop() {
	stat_bar.set_status("generating map");
	unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	hud.set_seed(seed);
	bool auto_center = false;

	Map map(4, actionbar_size + 3, viewport_rows, viewport_cols, seed, 0.08, 0.04);

	int x;
	for(x = 0; map.target_position(0, x) != CHAR_EMPTY; x++);

	Character player('@', 0, x);
	Character bla('E', 20, 20);

	map.init(0, 0);
	map.center(player.y(), player.x());
	map.add(&player);
	map.add(&bla);
	map.refresh();

	hud.set_pos(player.x(), player.y());
	hud.refresh();

	int ch = 0;
	stat_bar.set_status("idle");
	while (1) {
		ch = getch();
		stat_bar.set_status("", false);
		int dx = 0;
		int dy = 0;
		int act = -1;

		switch(ch) {
		case 'a':
			dx = -1;
			break;
		case 'd':
			dx = 1;
			break;
		case 'w':
			dy = -1;
			break;
		case 's':
			dy = 1;
			break;
		case KEY_UP:
			act_bar.move_up();
			break;
		case KEY_DOWN:
			act_bar.move_down();
			break;
		case '\n': case ' ':
			act = act_bar.get_action().action_no();
			break;

		}

		switch(act) {
		case ACTION_QUIT:
			return 0;
		case ACTION_CENTER:
			map.center(player.y(), player.x());
			break;
		case ACTION_AUTO_CENTER:
			auto_center = !auto_center;
			hud.set_auto_center(auto_center);
			break;
		case ACTION_DIG:
			if(map.target_position(player.y(), player.x()) == CHAR_TREASURE) {
				int loot = Loot::generate_loot(player.y(), player.x());
				hud.add_points(loot);
				stat_bar.set_status("collected loot");
			}
			act_bar.remove_action(ACTION_DIG);
		}

		char target = map.target_position(player.y() + dy, player.x() + dx);

		switch(target) {
		case CHAR_TREASURE:
			if(dx != 0 || dy != 0) act_bar.add_action(ACTION_DIG);
			player.move(dy, dx);
			break;
		case CHAR_GRASS: case CHAR_TALLGRASS: case CHAR_EMPTY:
			act_bar.remove_action(ACTION_DIG);
			player.move(dy, dx);
			break;
		default:
			act_bar.remove_action(ACTION_DIG);
			stat_bar.set_status("can't move here!", false);
		}

		//player.move(dy, dx);
		//map.move(dy, dx);

		if(auto_center) map.center(player.y(), player.x());
		hud.set_pos(player.x(), player.y());

		map.refresh();
		stat_bar.refresh();
		hud.refresh();
		act_bar.refresh();
	}
	return 0;

}
