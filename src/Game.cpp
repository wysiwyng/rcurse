/**
 * the main game controller class
 *
 * @author wysiwyng
 */

#include <chrono>
#include <iostream>
#include "Game.h"
#include "Character.h"
#include "Defs.h"
#include "Loot.h"
#include "Serializer.h"

#define FACTOR_Y 0.08f
#define FACTOR_X 0.04f
#define TICK_RATE 200
#define TICK_MS 1000 / TICK_RATE

Game::Game(int rows, int cols, int _actionbar_size) :
height(rows),
width(cols),
viewport_cols(width - _actionbar_size - 4),
viewport_rows(height - 5),
actionbar_size(_actionbar_size),
hud(3, cols, 0, 0),
act_bar(rows - 6, _actionbar_size + 2, 3, 0),
stat_bar(3, _actionbar_size + 2, rows - 3, 0),
map(4, actionbar_size + 3, viewport_rows, viewport_cols, FACTOR_Y, FACTOR_X),
player(CHAR_PLAYER, 0, 0, 100),
seed(0),
tick_rate(TICK_MS),
auto_center(false)
{
	stat_bar.set_status("Early init");

	WINDOW *viewport_border = newwin(viewport_rows + 2, viewport_cols + 2, 3, actionbar_size + 2);
	wattrset(viewport_border, A_BOLD);
	box(viewport_border, 0, 0);

	wrefresh(viewport_border);

	hud.set_fps(1000 / tick_rate);

	hud.refresh();
	act_bar.refresh();
	stat_bar.set_status("Idle");
}

Game::~Game() {
	endwin();
}

int Game::main_menu() {
	act_bar.add_action(ACTION_START);
	act_bar.add_action(ACTION_SETTINGS);
	act_bar.add_action(ACTION_QUIT);
	act_bar.refresh();
	stat_bar.set_status("Main Menu");
	int ch = 0;
	int act = -1;
	int ret_code = -1;

	while(ret_code == -1) {
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

		if (act == ACTION_QUIT) ret_code = 0;
		else if (act == ACTION_SETTINGS) ret_code = 2;
		else if(act == ACTION_START) ret_code = 1;

		act_bar.refresh();
	}

	act_bar.remove_action(ACTION_START);
	act_bar.remove_action(ACTION_SETTINGS);
	act_bar.remove_action(ACTION_QUIT);
	act_bar.refresh();
	return ret_code;
}

int Game::settings() {
	act_bar.add_action(ACTION_SEED);
	act_bar.add_action(ACTION_TICKRATE);
	act_bar.add_action(ACTION_QUIT);

	act_bar.refresh();

	int ch = 0;
	int act = -1;
	int ret_code = -1;
	stat_bar.set_status("Settings");


	while(ret_code == -1) {
		ch = getch();
		stat_bar.set_status("Settings");

		act = -1;
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

		if(act == ACTION_QUIT) ret_code = 0;
		else if(act == ACTION_SEED) {
			seed = stat_bar.read_num("Enter Seed:");
			char temp[30];
			sprintf(temp, "Seed: %d", seed);
			stat_bar.set_status(temp);
		}
		else if(act == ACTION_TICKRATE) {
			tick_rate = stat_bar.read_num("Enter FPS:");
			char temp[30];
			sprintf(temp, "FPS: %d", tick_rate);
			stat_bar.set_status(temp);
			tick_rate = 1000 / tick_rate;
		}

		act_bar.refresh();
	}

	act_bar.remove_action(ACTION_SEED);
	act_bar.remove_action(ACTION_TICKRATE);
	act_bar.remove_action(ACTION_QUIT);
	return 0;
}

int Game::game_loop() {
	bool can_move = false, can_dig = false, could_dig = false, hurt = false;
	bool run = true;
	int x, ch, score = 300;

	Timer t;

	t.add_listener(this);
	t.interval(tick_rate);

	act_bar.add_action(ACTION_CENTER);
	act_bar.add_action(ACTION_AUTO_CENTER);
	act_bar.add_action(ACTION_QUIT);

	for(int i = 2; i <= 6; i++) act_bar.add_action(i);
	if(seed == 0) seed = std::chrono::system_clock::now().time_since_epoch().count();

	hud.set_seed(seed);
	map.set_seed(seed);

	for(x = 0; map.target_position(0, x) != CHAR_EMPTY; x++);

	player.pos(0, x);
	Character bla('E', 20, 20, 100);

	map.init(0, 0);
	map.center(player.y(), player.x());
	map.add(&player);
	map.add(&bla);

	hud.set_fps(1000 / tick_rate);
	hud.set_pos(player.x(), player.y());
	hud.set_points(score);

	stat_bar.set_status("idle", false);

	on_timer();

	t.start();

	while (run) {
		ch = getch();
		mtx.lock();
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
			//t.stop();
			run = false;
			break;
		case ACTION_CENTER:
			map.center(player.y(), player.x());
			break;
		case ACTION_AUTO_CENTER:
			auto_center = !auto_center;
			hud.set_auto_center(auto_center);
			break;
		case ACTION_DIG:
			if(map.target_position(player.y(), player.x(), false) == CHAR_TREASURE) {
				int loot = Loot::instance().generate_loot(player.y(), player.x());
				score += loot;
				hud.set_points(score);
				stat_bar.set_status("collected loot", false);
			}
			act_bar.remove_action(ACTION_DIG);
			break;
		case ACTION_HEAL:
			if(score > 30) {
				score -= 30;
				hud.set_points(score);
				player.lose_health(-50);
				hud.set_hp(player.health());
				stat_bar.set_status("gained 50 hp");
			} else {
				stat_bar.set_status("not enough points!");
			}
			break;
		case ACTION_UPGRADE_SWIM:
			if(score > 20) {
				score -= 20;
				hud.set_points(score);
				player.water(true);
				stat_bar.set_status("you can now swim!");
				hud.set_swim(true);
			} else {
				stat_bar.set_status("not enough points!");
			}
			break;
		case ACTION_UPGRADE_CLIMB:
			if(score > 50) {
				score -= 50;
				hud.set_points(score);
				player.climb(true);
				stat_bar.set_status("you can now climb mountains!");
				hud.set_climb(true);
			} else {
				stat_bar.set_status("not enough points!");
			}
			break;
		case ACTION_UPGRADE_ICE:
			if(score > 30) {
				score -= 30;
				hud.set_points(score);
				player.ice(true);
				stat_bar.set_status("you can now go over ice!");
				hud.set_ice(true);
			} else {
				stat_bar.set_status("not enough points!");
			}
			break;
		case ACTION_SAVE:
			Serializer::instance().save("asd");
			break;
		}

		char target = map.target_position(player.tempy() + dy, player.tempx() + dx);

		switch(target) {
		case CHAR_TREASURE:
			can_dig = true;
			can_move = true;
			hurt = false;
			break;
		case CHAR_GRASS: case CHAR_TALLGRASS: case CHAR_EMPTY:
			can_dig = false;
			hurt = false;
			can_move = true;
			break;
		case CHAR_ENEMY:
			can_move = false;
			can_dig = false;
			hurt = true;
			break;
		case CHAR_WATER: case CHAR_WALL: case CHAR_ICE:
			if((player.water() && target == CHAR_WATER) || (player.climb() && target == CHAR_WALL) || (player.ice() && target == CHAR_ICE)) {
				can_dig = false;
				hurt = false;
				can_move = true;
				break;
			}
		default:
			stat_bar.set_status("can't move here!", false);
			can_move = false;
			can_dig = false;
			hurt = false;
		}

		if(can_move) player.move(dy, dx);
		if(hurt) {
			stat_bar.set_status("ouch!", false);
			player.lose_health(10);
		}
		if(can_dig && !could_dig) {
			act_bar.add_action(ACTION_DIG);
		}
		if(!can_dig && could_dig) {
			act_bar.remove_action(ACTION_DIG);
		}

		could_dig = can_dig;

		hud.set_hp(player.health());

		mtx.unlock();
	}
	t.stop();
	act_bar.remove_action(ACTION_CENTER);
	act_bar.remove_action(ACTION_AUTO_CENTER);
	act_bar.remove_action(ACTION_QUIT);

	for(int i = 2; i <= 6; i++) act_bar.remove_action(i);
	return 0;
}

void Game::on_timer() {
	mtx.lock();
	player.update();
	if(auto_center) map.center(player.y(), player.x());
	hud.set_pos(player.x(), player.y());
	map.refresh();
	stat_bar.refresh();
	hud.refresh();
	act_bar.refresh();
	// ai actions

	mtx.unlock();
}
