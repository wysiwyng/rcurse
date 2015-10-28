/*
 * TimerListener.hpp
 * a timer listener event interface
 *  Created on: Apr 15, 2015
 * @author: wysiwyng
 */

#ifndef TIMERLISTENER_H_
#define TIMERLISTENER_H_

#include <functional>

namespace rcurse {

class TimerListener {
public:
	/**
	 * TimerListener default constructor, will generate an id or use the given one if != 0
	 * @param the listeners default UID
	 */
	TimerListener(int newid = 0);

	/**
	 * TimerListener destructor
	 */
	virtual ~TimerListener();

	/**
	 * the callback funtion
	 */
	virtual void on_timer() = 0;

	/**
	 * equals operator for usage in data structures
	 */
	bool operator==(const TimerListener &other) const {
		return _id == other._id;
	}

	/**
	 * @returns the listeners id
	 */
	int id() const;
private:
	/**
	 * the listeners id
	 */
	int _id;
};
}
/**
 * a hash function for a TimerListener
 */
namespace std {
template<>
class hash<rcurse::TimerListener> {
public:
	size_t operator()(const rcurse::TimerListener &listener) const {
		return hash<int>()(listener.id());
	}
};
}

#endif /* TIMERLISTENER_H_ */
