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
#define RUN_RATE 20

Game::Game(int rows, int cols, int _actionbar_size) :
height(rows),
width(cols),
viewport_cols(width - _actionbar_size - 4),
viewport_rows(height - 5),
actionbar_size(_actionbar_size),
hud(3, cols, 0, 0),
act_bar(rows - 6, _actionbar_size + 2, 3, cols - _actionbar_size - 2),
stat_bar(3, _actionbar_size + 2, rows - 3, cols - _actionbar_size - 2),
map(4, 1, viewport_rows, viewport_cols, FACTOR_Y, FACTOR_X),
player(CHAR_PLAYER, 0, 0, 100),
walk_counter(0),
run_counter(0)
{
	game_options.seed = 0;
	game_options.score = 0;
	game_options.tick_rate = TICK_MS;
	game_options.auto_center = false;
	movement = {0,0,0};
	stat_bar.set_status("Early init");

	WINDOW *viewport_border = newwin(viewport_rows + 2, viewport_cols + 2, 3, 0);
	wattrset(viewport_border, A_BOLD);
	box(viewport_border, 0, 0);

	wrefresh(viewport_border);

	hud.add_game_options(&game_options);
	hud.add_player(&player);

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
				game_options.seed = ser.seed();
				game_options.score = ser.score();
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
			game_options.seed = stat_bar.read_num("Enter Seed:");
			char temp[30];
			sprintf(temp, "Seed: %d", game_options.seed);
			stat_bar.set_status(temp);
		}
		else if(act == Action::ACTION_TICKRATE) {
			game_options.tick_rate = stat_bar.read_num("Enter FPS:");
			char temp[30];
			sprintf(temp, "FPS: %d", game_options.tick_rate);
			stat_bar.set_status(temp);
			game_options.tick_rate = 1000 / game_options.tick_rate;
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
	t.interval(game_options.tick_rate);

	act_bar.add_action(Action::ACTION_CENTER);
	act_bar.add_action(Action::ACTION_AUTO_CENTER);
	act_bar.add_action(Action::ACTION_SAVE);
	act_bar.add_action(Action::ACTION_QUIT);

	for(int i = 2; i <= 6; i++) act_bar.add_action(i);

	if(game_options.seed == 0) game_options.seed = std::chrono::system_clock::now().time_since_epoch().count();

	map.set_seed(game_options.seed);

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
		case 'a': case 'A':
			dx = -1;
			break;
		case 'd': case 'D':
			dx = 1;
			break;
		case 'w': case 'W':
			dy = -1;
			break;
		case 's': case 'S':
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
		
		if(ch == 'A' || ch == 'D' || ch == 'S' || ch == 'W')
			movement.sprint = true;
		else movement.sprint = false;

		switch(act) {
		case Action::ACTION_QUIT:
			//t.stop();
			run = false;
			break;
		case Action::ACTION_CENTER:
			map.center(player.y(), player.x());
			break;
		case Action::ACTION_AUTO_CENTER:
			game_options.auto_center = !game_options.auto_center;
			break;
		case Action::ACTION_DIG:
			if(map.target_position(player.y(), player.x(), false) == CHAR_TREASURE) {
				int loot = Loot::instance().generate_loot(player.y(), player.x());
				game_options.score += loot;
				stat_bar.set_status("collected loot", false);
			}
			act_bar.remove_action(Action::ACTION_DIG);
			break;
		case Action::ACTION_HEAL:
			if(game_options.score > 30) {
				game_options.score -= 30;
				player.set_health(player.health() + 50);
				stat_bar.set_status("gained 50 hp");
			} else {
				stat_bar.set_status("not enough points!");
			}
			break;
		case Action::ACTION_UPGRADE_SWIM:
			if(game_options.score >= 20) {
				game_options.score -= 20;
				player.water(true);
				stat_bar.set_status("you can now swim!");
			} else {
				stat_bar.set_status("not enough points!");
			}
			break;
		case Action::ACTION_UPGRADE_CLIMB:
			if(game_options.score >= 50) {
				game_options.score -= 50;
				//hud.set_points(score);
				player.climb(true);
				stat_bar.set_status("you can now climb mountains!");
				//hud.set_climb(true);
			} else {
				stat_bar.set_status("not enough points!");
			}
			break;
		case Action::ACTION_UPGRADE_ICE:
			if(game_options.score >= 30) {
				game_options.score -= 30;
				player.ice(true);
				stat_bar.set_status("you can now go over ice!");
			} else {
				stat_bar.set_status("not enough points!");
			}
			break;
		case Action::ACTION_SAVE:
			Serializer& ser = Serializer::instance();
			ser.clear();
			ser.add_seed(game_options.seed);
			ser.add_player(player);
			ser.add_character(&enemies);
			ser.add_loot_pos(Loot::instance().save_positions());
			ser.add_score(game_options.score);
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

		mtx.unlock();
	}
	t.stop();
	act_bar.clear();
	game_options.seed = 0;
	game_options.score = 0;
	enemies.clear();
	Loot::instance().clear();
	player.pos(0, 0);
	player.set_health(100);
	return 0;
}

void Game::do_move() {
	old_movement.dx = movement.dx;
	old_movement.dy = movement.dy;
	player.move(movement.dy, movement.dx);
	movement.dy = 0;
	movement.dx = 0;
	player.update();
}

void Game::on_timer() {
	mtx.lock();
	
	if(movement.dx != 0 || movement.dy != 0) {
		if(old_movement.dx == 0 && old_movement.dy == 0) {
			do_move();
			walk_counter = 0;
			run_counter = 0;
		}
		if(walk_counter > TICK_RATE / ACTION_RATE && movement.sprint == false) {
			do_move();
			walk_counter = 0;
		}
		if(run_counter > TICK_RATE / RUN_RATE && movement.sprint == true) {
			do_move();
			run_counter = 0;
		}
		run_counter++;
		walk_counter++;	
	}

	if(game_options.auto_center) map.center(player.y(), player.x());
	map.refresh();
	stat_bar.refresh();
	hud.refresh();
	act_bar.refresh();
	// ai actions

	mtx.unlock();
}
}
