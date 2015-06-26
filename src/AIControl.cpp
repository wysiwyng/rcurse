/*
 * AIControl.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: wysiwyng
 */

#include "AIControl.h"
namespace rcurse {
AIControl::AIControl() {
	// TODO Auto-generated constructor stub

}

AIControl::~AIControl() {
	// TODO Auto-generated destructor stub
}

AIControl& AIControl::instance() {
	static AIControl _instance;
	return _instance;
}
}
