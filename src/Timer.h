/*
 * Timer.h
 *
 * @author: wysiwyng
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <thread>
#include <vector>
#include <unordered_set>
#include "TimerListener.h"

namespace rcurse {

/**
 * a very basic periodic timer
 */
class Timer {
private:
	std::unordered_set<TimerListener*> listeners;
	std::thread worker;

	volatile bool _running, _stop;
	int _interval;

	void do_work();
public:
	/**
	 * Timer Constructor
	 * @param func the callback function
	 * @param interval the delay between calls of the callback function
	 */
	Timer();

	/**
	 * Timer destructor
	 */
	virtual ~Timer();

	/**
	 * starts the timer initially
	 */
	void start();

	/**
	 * pauses the timer
	 */
	void pause();

	/**
	 * resumes a paused timer
	 */
	void resume();

	/**
	 * stops and destroys a timer
	 */
	void stop();

	/**
	 * @returns the set interval
	 */
	int interval();

	/**
	 * sets the interval
	 * @param _int the new interval
	 */
	void interval(int _int);

	/**
	 * registers a listener
	 * @param listener the listener
	 */
	void add_listener(TimerListener *listener);

	/**
	 * removes a listener
	 * @param listener the listener to remove
	 */

	void remove_listener(TimerListener *listener);

};
}
#endif /* TIMER_H_ */
