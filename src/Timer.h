/*
 * Timer.h
 *
 * @author: wysiwyng
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <functional>
#include <thread>

/**
 * a very basic periodic timer
 */
class Timer {
private:
	volatile bool _running, _stop;
	int _interval;
	std::function<void(void)> _func;
	std::thread worker;
	void do_work();

public:
	/**
	 * Timer Constructor
	 * @param func the callback function
	 * @param interval the delay between calls of the callback function
	 */
	Timer(std::function<void(void)> func, int interval);

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
};

#endif /* TIMER_H_ */
