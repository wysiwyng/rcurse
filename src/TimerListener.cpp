/*
 * TimerListener.cpp
 *
 *  Created on: Apr 15, 2015
 *      Author: wysiwyng
 */
#include <chrono>
#include "TimerListener.h"

TimerListener::TimerListener(int newid) {
	if(!newid) _id = newid;
	else {
		_id = std::chrono::system_clock::now().time_since_epoch().count();
	}
}

TimerListener::~TimerListener() {

}

int TimerListener::id() const{
	return _id;
}
