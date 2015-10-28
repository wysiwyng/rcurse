/**
 * the main game controller class
 *
 * @author wysiwyng
 */

#include <chrono>
#include <iostream>
#include "Game.hpp"
#include "Character.hpp"
#include "Defs.hpp"
#include "Loot.hpp"
#include "Serializer.hpp"

namespace rcurse {

#define FACTOR_Y 0.08f
#define FACTOR_X 0.04f
#define TICK_RATE 200
#define TICK_MS 1000 / TICK_RATE
#define ACTION_RATE 10

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
seed(0), score(0),
tick_rate(TICK_MS),
action_counter(0),
auto_center(false)
{
	movement = {0,0,0};
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
	act_bar.add_action(Action::ACTION_START);
	act_bar.add_action(Action::ACTION_LOAD);
	act_bar.add_action(Action::ACTION_SETTINGS);
	act_bar.add_action(Action::ACTION_QUIT);
	act_bar.refresh();
	stat_bar.set_status("Main Menu");
	int ch = 0;
	int act = -1;
	int ret_code = RET_CONTINUE;

	while(ret_code == RET_CONTINUE) {
		ch = getch();
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

		if (act == Action::ACTION_QUIT) ret_code = RET_QUIT;
		else if (act == Action::ACTION_SETTINGS) ret_code = RET_SETTINGS;
		else if(act == Action::ACTION_START) ret_code = RET_START;
		else if(act == Action::ACTION_LOAD) {
			Serializer& ser = Serializer::instance();

			int no = stat_bar.read_num("Enter save number>");

			char buf[80];

			sprintf(buf, "rsave-%04d.xml", no);

			if(!ser.read(buf)) stat_bar.set_status("error loading save!");
			else {
				stat_bar.set_status("last save loaded");
				seed = ser.seed();
				score = ser.score();
				player = ser.player();
				enemies = ser.char_vec();
				Loot::instance().add_positions(ser.pos_set());
				ret_code = RET_LOAD;
			}
		}

		act_bar.refresh();
	}

	act_bar.clear();
	return ret_code;
}

int Game::settings() {
	act_bar.add_action(Action::ACTION_SEED);
	act_bar.add_action(Action::ACTION_TICKRATE);
	act_bar.add_action(Action::ACTION_QUIT);

	act_bar.refresh();

	int ch = 0;
	int act = -1;
	int ret_code = RET_CONTINUE;
	stat_bar.set_status("Settings");


	while(ret_code == RET_CONTINUE) {
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

		if(act == Action::ACTION_QUIT) ret_code = 0;
		else if(act == Action::ACTION_SEED) {
			seed = stat_bar.read_num("Enter Seed:");
			char temp[30];
			sprintf(temp, "Seed: %d", seed);
			stat_bar.set_status(temp);
		}
		else if(act == Action::ACTION_TICKRATE) {
			tick_rate = stat_bar.read_num("Enter FPS:");
			char temp[30];
			sprintf(temp, "FPS: %d", tick_rate);
			stat_bar.set_status(temp);
			tick_rate = 1000 / tick_rate;
		}

		act_bar.refresh();
	}

	act_bar.clear();
	return 0;
}

int Game::game_loop(bool from_save) {
	bool can_move = false, can_dig = false, could_dig = false, hurt = false;
	bool run = true;
	int x, ch;

	Timer t;

	t.add_listener(this);
	t.interval(tick_rate);

	act_bar.add_action(Action::ACTION_CENTER);
	act_bar.add_action(Action::ACTION_AUTO_CENTER);
	act_bar.add_action(Action::ACTION_SAVE);
	act_bar.add_action(Action::ACTION_QUIT);

	for(int i = 2; i <= 6; i++) act_bar.add_action(i);

	if(seed == 0) seed = std::chrono::system_clock::now().time_since_epoch().count();

	hud.set_seed(seed);
	map.set_seed(seed);

	if(!from_save) {
		for(x = 0; map.target_position(0, x) != CHAR_EMPTY; x++);

		player.pos(0, x);
		Character bla('E', 20, 20, 100);
		enemies.push_back(bla);
	}

	map.init(0, 0);
	map.center(player.y(), player.x());
	map.add(&player);
	map.add(&enemies);

	hud.set_fps(1000 / tick_rate);
	hud.set_pos(player.x(), player.y());
	hud.set_points(score);
	hud.set_climb(player.climb());
	hud.set_ice(player.ice());
	hud.set_swim(player.water());

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
		case Action::ACTION_QUIT:
			//t.stop();
			run = false;
			break;
		case Action::ACTION_CENTER:
			map.center(player.y(), player.x());
			break;
		case Action::ACTION_AUTO_CENTER:
			auto_center = !auto_center;
			hud.set_auto_center(auto_center);
			break;
		case Action::ACTION_DIG:
			if(map.target_position(player.y(), player.x(), false) == CHAR_TREASURE) {
				int loot = Loot::instance().generate_loot(player.y(), player.x());
				score += loot;
				hud.set_points(score);
				stat_bar.set_status("collected loot", false);
			}
			act_bar.remove_action(Action::ACTION_DIG);
			break;
		case Action::ACTION_HEAL:
			if(score > 30) {
				score -= 30;
				hud.set_points(score);
				player.set_health(player.health() + 50);
				hud.set_hp(player.health());
				stat_bar.set_status("gained 50 hp");
			} else {
				stat_bar.set_status("not enough points!");
			}
			break;
		case Action::ACTION_UPGRADE_SWIM:
			if(score >= 20) {
				score -= 20;
				hud.set_points(score);
				player.water(true);
				stat_bar.set_status("you can now swim!");
				hud.set_swim(true);
			} else {
				stat_bar.set_status("not enough points!");
			}
			break;
		case Action::ACTION_UPGRADE_CLIMB:
			if(score >= 50) {
				score -= 50;
				hud.set_points(score);
				player.climb(true);
				stat_bar.set_status("you can now climb mountains!");
				hud.set_climb(true);
			} else {
				stat_bar.set_status("not enough points!");
			}
			break;
		case Action::ACTION_UPGRADE_ICE:
			if(score >= 30) {
				score -= 30;
				hud.set_points(score);
				player.ice(true);
				stat_bar.set_status("you can now go over ice!");
				hud.set_ice(true);
			} else {
				stat_bar.set_status("not enough points!");
			}
			break;
		case Action::ACTION_SAVE:
			Serializer& ser = Serializer::instance();
			ser.clear();
			ser.add_seed(seed);
			ser.add_player(player);
			ser.add_character(&enemies);
			ser.add_loot_pos(Loot::instance().save_positions());
			ser.add_score(score);
			int no = stat_bar.read_num("Enter save number>");
			no = ser.save(no);
			if(no == -1) stat_bar.set_status("saving failed!");
			else {
				char buf[80];
				sprintf(buf, "save no: %04d", no);
				stat_bar.set_status(buf);
			}
			break;
		}

		char target = map.target_position(player.tempy() + dy, player.tempx() + dx);

		switch(target) {
		case CHAR_TREASURE:
			can_dig = true;
			can_move = true;
			hurt = false;
			break;
		case CHAR_GRASS: case CHAR_TALLGRASS: case CHAR_EMPTY: case CHAR_FLOWER:
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

		if(can_move) {
			movement.dy = dy;
			movement.dx = dx;
		}
		if(hurt) {
			stat_bar.set_status("ouch!", false);
			player.set_health(player.health() - 10);
		}
		if(can_dig && !could_dig) {
			act_bar.add_action(Action::ACTION_DIG);
		}
		if(!can_dig && could_dig) {
			act_bar.remove_action(Action::ACTION_DIG);
		}

		could_dig = can_dig;

		if(player.health() <= 0) {
			stat_bar.set_status("you died!");
			run = false;
			getch();
		}

		hud.set_hp(player.health());

		mtx.unlock();
	}
	t.stop();
	act_bar.clear();
	seed = 0;
	score = 0;
	enemies.clear();
	Loot::instance().clear();
	player.pos(0, 0);
	player.set_health(100);
	return 0;
}

void Game::on_timer() {
	mtx.lock();
	if(action_counter > TICK_RATE / ACTION_RATE) {
		action_counter = 0;
		player.move(movement.dy, movement.dx);
		player.update();
		movement.dy = 0;
		movement.dx = 0;
		movement.sprint = 0;
	} else action_counter++;

	if(auto_center) map.center(player.y(), player.x());
	hud.set_pos(player.x(), player.y());
	map.refresh();
	stat_bar.refresh();
	hud.refresh();
	act_bar.refresh();
	// ai actions

	mtx.unlock();
}
}
