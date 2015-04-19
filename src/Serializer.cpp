/*
 * Serializer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wysiwyng
 */

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <pugixml.hpp>
#include "Serializer.h"

Serializer::Serializer() :
_seed(0),
_score(0)
{ }

Serializer& Serializer::instance() {
	static Serializer _instance;
	return _instance;
}

void Serializer::add_character(Character & chr) {
	_chars.push_back(chr);
}

void Serializer::clear_characters() {
	_chars.clear();
}

void Serializer::add_loot_pos(int y, int x) {
	position temp{y, x};
	_positions.insert(temp);
}

void Serializer::add_loot_pos(std::unordered_set<position> const * const pos) {
	_positions.insert((*pos).begin(), (*pos).end());
}

void Serializer::clear_lot_pos() {
	_positions.clear();
}

void Serializer::add_score(int score) {
	_score = score;
}

void Serializer::add_seed(unsigned int seed) {
	_seed = seed;
}

void Serializer::save() {
	time_t now = time(0);
	struct tm tstruct = *localtime(&now);
	char buf[80];
	strftime(buf, sizeof(buf), "%d%m%Y-%H%M%S", &tstruct);

	pugi::xml_document doc;

	pugi::xml_node save_game = doc.append_child("savegame");

	pugi::xml_node score = save_game.append_child("score");
	score.append_attribute("value") = _score;

	pugi::xml_node seed = save_game.append_child("seed");
	seed.append_attribute("value") = _seed;

	pugi::xml_node positions = save_game.append_child("loot-positions");
	for(std::unordered_set<position>::iterator it = _positions.begin(); it != _positions.end(); it++) {
		pugi::xml_node pos = positions.append_child("position");
		pos.append_child("y").append_attribute("value") = (*it).y;
		pos.append_child("x").append_attribute("value") = (*it).x;
	}

	pugi::xml_node chars = save_game.append_child("characters");
	for(std::vector<Character>::iterator it = _chars.begin(); it != _chars.end(); it++) {
		pugi::xml_node chr = chars.append_child("char");
		chr.append_child("y").append_attribute("value") = (*it).y();
		chr.append_child("x").append_attribute("value") = (*it).x();
		chr.append_child("tempy").append_attribute("value") = (*it).tempy();
		chr.append_child("tempx").append_attribute("value") = (*it).tempx();
		chr.append_child("oldy").append_attribute("value") = (*it).oldy();
		chr.append_child("oldx").append_attribute("value") = (*it).oldx();
		chr.append_child("symbol").append_attribute("value") = (*it).symbol();
		chr.append_child("needs-redraw").append_attribute("value") = (*it).needs_redraw();
		chr.append_child("is-visible").append_attribute("value") = (*it).is_visible();
		chr.append_child("health").append_attribute("value") = (*it).health();
		chr.append_child("water").append_attribute("value") = (*it).water();
		chr.append_child("climb").append_attribute("value") = (*it).climb();
		chr.append_child("ice").append_attribute("value") = (*it).ice();
	}
	save_game.append_attribute("date") = buf;
	doc.print(std::cerr);
}

void Serializer::clear() {
	_chars.clear();
	_positions.clear();
	_seed = 0;
	_score = 0;
}
