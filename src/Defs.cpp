/**
 * Global definitions in a seperate namespace
 *
 * @author wysiwyng
 */

#include <curses.h>
#include "Defs.h"
#include "Loot.h"

namespace Defs {

void init_colors(){
	init_pair(COLOR_PLAYER,COLOR_MAGENTA,COLOR_BLACK);
	init_pair(COLOR_ENEMY,COLOR_RED,COLOR_BLACK);
	init_pair(COLOR_WATER,COLOR_WHITE,COLOR_BLUE);
	init_pair(COLOR_GRASS,COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_WALL,COLOR_WHITE,COLOR_BLACK);
	init_pair(COLOR_ICE,COLOR_BLACK,COLOR_WHITE);
	init_pair(COLOR_TREASURE,COLOR_YELLOW,COLOR_BLACK);
}

short get_color(char symbol){
	switch(symbol){
	case CHAR_PLAYER:
		return COLOR_PLAYER;
	case CHAR_ENEMY:
		return COLOR_ENEMY;
	case CHAR_WATER:
		return COLOR_WATER;
	case CHAR_GRASS: case CHAR_TALLGRASS:
		return COLOR_GRASS;
	case CHAR_WALL:
		return COLOR_WALL;
	case CHAR_ICE:
		return COLOR_ICE;
	case CHAR_TREASURE:
		return COLOR_TREASURE;
	case CHAR_LOOTED:
		return CHAR_GRASS;
	}
	return 0;
}

void set_color(WINDOW *w, char chr) {
	switch (chr) {
	case CHAR_PLAYER:
		wattrset(w, A_BOLD | COLOR_PAIR(COLOR_PLAYER));
		break;
	case CHAR_ENEMY:
		wattrset(w, A_BOLD | COLOR_PAIR(COLOR_ENEMY));
		break;
	case CHAR_WATER:
		wattrset(w, A_DIM | COLOR_PAIR(COLOR_WATER));
		break;
	case CHAR_GRASS:
		wattrset(w, COLOR_PAIR(COLOR_GRASS));
		break;
	case CHAR_TALLGRASS:
		wattrset(w, A_BOLD | COLOR_PAIR(COLOR_GRASS));
		break;
	case CHAR_WALL:
		wattrset(w, COLOR_PAIR(COLOR_WALL));
		break;
	case CHAR_ICE:
		wattrset(w, A_BOLD | COLOR_PAIR(COLOR_ICE));
		break;
	case CHAR_TREASURE:
		wattrset(w, A_BOLD | COLOR_PAIR(COLOR_TREASURE));
		break;
	case CHAR_EMPTY:
		wattrset(w, 0);
		break;
	}
}

}

