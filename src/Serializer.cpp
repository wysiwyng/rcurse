/*
 * Serializer.hpp
 * a serializer class to save and load game data to xml
 *  Created on: Apr 17, 2015
 *  @author: wysiwyng
 */

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include "Serializer.hpp"

namespace rcurse {

Serializer::Serializer() :
_player('@', 0, 0, 0),
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

void Serializer::add_player(Character player) {
	_player = player;
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

int Serializer::save() {
	return save(-1);
}

int Serializer::save(int slot) {
	time_t now = time(0);
	struct tm tstruct = *localtime(&now);
	char buf[80];
	strftime(buf, sizeof(buf), "%d%m%Y-%H%M%S", &tstruct);

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

	pugi::xml_node player = chars.append_child("player");
	player.append_attribute("y") = _player.y();
	player.append_attribute("x") = _player.x();
	player.append_attribute("symbol") = _player.symbol();
	player.append_attribute("needs-redraw") = _player.needs_redraw();
	player.append_attribute("is-visible") = _player.is_visible();
	player.append_attribute("health") = _player.health();
	player.append_attribute("water") = _player.water();
	player.append_attribute("climb") = _player.climb();
	player.append_attribute("ice") = _player.ice();

	for(std::vector<Character>::iterator it = _chars.begin(); it != _chars.end(); it++) {
		pugi::xml_node chr = chars.append_child("enemy");
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
	
	if(slot == -1) {
		for(slot = 0; slot < 1000; slot++) {
			sprintf(buf, "rsave-%04d.xml", slot);
			std::ifstream file(buf);
			if(!file.good()) break;
		}
	}
	sprintf(buf, "rsave-%04d.xml", slot);
	_doc.save_file(buf);
	return slot;	
}

void Serializer::clear() {
	_chars.clear();
	_positions.clear();
	_seed = 0;
	_score = 0;
}

bool Serializer::read(char * fname) {
	//pugi::xml_parse_result bla = _doc.load_file(fname);
	bool ret = _doc.load_file(fname);

	pugi::xml_node sg = _doc.child("savegame");

	_score = sg.child("score").attribute("value").as_int();
	_seed = sg.child("seed").attribute("value").as_uint();

	pugi::xml_node positions = sg.child("loot-positions");

	for(pugi::xml_node pos = positions.child("position"); pos; pos = pos.next_sibling("position")) {
		position temp = {pos.attribute("y").as_int(), pos.attribute("x").as_int()};
		_positions.insert(temp);
	}

	pugi::xml_node characters = sg.child("characters");

	pugi::xml_node player = characters.child("player");

	Character temp_player(player.attribute("symbol").as_int(), player.attribute("y").as_int(), player.attribute("x").as_int(), player.attribute("health").as_int());
	temp_player.climb(player.attribute("climb").as_bool());
	temp_player.ice(player.attribute("ice").as_bool());
	temp_player.water(player.attribute("water").as_bool());
	if(!player.attribute("is-visible").as_bool()) temp_player.reset_visible();
	if(!player.attribute("redraw").as_bool()) temp_player.reset_redraw();
	_player = temp_player;

	for(pugi::xml_node chr = characters.child("enemy"); chr; chr = chr.next_sibling("enemy")) {
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

int Serializer::score() {
	return _score;
}

unsigned int Serializer::seed() {
	return _seed;
}

Character Serializer::player() {
	return _player;
}

std::vector<Character> Serializer::char_vec() {
	return _chars;
}

std::unordered_set<position> Serializer::pos_set() {
	return _positions;
}
}
