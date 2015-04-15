/*
 * Timer.cpp
 *
 *  Created on: Apr 14, 2015
 *  @author: wysiwyng
 */

#include <iostream>
#include <chrono>

#include "Timer.h"

Timer::Timer(std::function<void(void)> func, int interval) :
_running(false), _stop(false),
_interval(interval),
_func(func)
{
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

void Timer::start() {
	_running = true;
	worker = std::thread(std::bind(&Timer::do_work, this));

}

void Timer::stop() {
	_running = false;
	_stop = true;
	worker.join();
}

void Timer::pause() {
	_running = false;
}

void Timer::resume() {
	_running = true;
}

void Timer::do_work() {
	while(!_stop) {
		if(_running) {
			for(std::vector<TimerListener*>::iterator it = listeners.begin(); it != listeners.end(); it++) {
				(**it).on_timer();
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(_interval));
	}
}

int Timer::interval() {
	return _interval;
}

void Timer::interval(int _int) {
	_interval = _int;
}

void Timer::add_listener(TimerListener *listener) {
	listeners.push_back(listener);
}
