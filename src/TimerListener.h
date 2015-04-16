/*
 * TimerListener.h
 *
 *  Created on: Apr 15, 2015
 *      Author: wysiwyng
 */

#ifndef TIMERLISTENER_H_
#define TIMERLISTENER_H_

#include <functional>

class TimerListener {
public:
	TimerListener(int newid = 0);
	virtual ~TimerListener();
	virtual void on_timer() = 0;

	/**
	 * equals operator for usage in data structures
	 */
	bool operator==(const TimerListener &other) const {
		return _id == other._id;
	}

	int id() const;
private:
	int _id;
};

namespace std {
template<>
class hash<TimerListener> {
public:
	size_t operator()(const TimerListener &listener) const {
		return hash<int>()(listener.id());
	}
};
}

#endif /* TIMERLISTENER_H_ */
