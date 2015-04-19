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

void Serializer::add_character(std::vector<Character> const * const chrs) {
	_chars.insert(_chars.end(), (*chrs).begin(), (*chrs).end());
}

void Serializer::clear_characters() {
	_chars.clear();
}

void Serializer::add_loot_pos(int y, int x) {
	position temp = {y, x};
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
	strftime(buf, sizeof(buf), "%d%m%Y-%H%M%S.xml", &tstruct);

	_doc.reset();

	pugi::xml_node save_game = _doc.append_child("savegame");

	pugi::xml_node score = save_game.append_child("score");
	score.append_attribute("value") = _score;

	pugi::xml_node seed = save_game.append_child("seed");
	seed.append_attribute("value") = _seed;

	pugi::xml_node positions = save_game.append_child("loot-positions");
	for(std::unordered_set<position>::iterator it = _positions.begin(); it != _positions.end(); it++) {
		pugi::xml_node pos = positions.append_child("position");
		pos.append_attribute("y") = (*it).y;
		pos.append_attribute("x") = (*it).x;
	}

	pugi::xml_node chars = save_game.append_child("characters");
	for(std::vector<Character>::iterator it = _chars.begin(); it != _chars.end(); it++) {
		pugi::xml_node chr = chars.append_child("char");
		chr.append_attribute("y") = (*it).y();
		chr.append_attribute("x") = (*it).x();
		chr.append_attribute("symbol") = (*it).symbol();
		chr.append_attribute("needs-redraw") = (*it).needs_redraw();
		chr.append_attribute("is-visible") = (*it).is_visible();
		chr.append_attribute("health") = (*it).health();
		chr.append_attribute("water") = (*it).water();
		chr.append_attribute("climb") = (*it).climb();
		chr.append_attribute("ice") = (*it).ice();
	}
	save_game.append_attribute("date") = buf;
	//doc.print(std::cerr);

	_doc.save_file(buf);
}

void Serializer::clear() {
	_chars.clear();
	_positions.clear();
	_seed = 0;
	_score = 0;
}

bool Serializer::read(char * fname) {
	bool ret = _doc.load_file(fname);

	pugi::xml_node sg = _doc.child("savegame");

	_score = sg.child("score").attribute("value").as_int();
	_seed = sg.child("seed").attribute("value").as_uint();

	pugi::xml_node positions = _doc.child("loot-positions");

	for(pugi::xml_node pos = positions.child("position"); pos; pos = pos.next_sibling("position")) {
		position temp = {pos.attribute("y").as_int(), pos.attribute("x").as_int()};
		_positions.insert(temp);
	}

	pugi::xml_node characters = _doc.child("characters");

	for(pugi::xml_node chr = characters.child("char"); chr; chr.next_sibling("char")) {
		Character temp(chr.attribute("symbol").as_int(), chr.attribute("y").as_int(), chr.attribute("x").as_int(), chr.attribute("health").as_int());
		temp.climb(chr.attribute("climb").as_bool());
		temp.ice(chr.attribute("ice").as_bool());
		temp.water(chr.attribute("water").as_bool());
		if(!chr.attribute("is-visible").as_bool()) temp.reset_visible();
		if(!chr.attribute("redraw").as_bool()) temp.reset_redraw();
		_chars.push_back(temp);
	}

	return ret;
}
