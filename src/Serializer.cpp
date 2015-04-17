/*
 * Serializer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wysiwyng
 */

#include <iostream>
#include <fstream>
#include <pugixml.hpp>
#include "Serializer.h"

Serializer::Serializer() :
_seed(0)
{ }

Serializer& Serializer::instance() {
	static Serializer _instance;
	return _instance;
}

void Serializer::save(const char * fname) {
	std::ofstream outfile;
	outfile.open(fname);
}
