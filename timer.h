/*
 * timer.h
 *
 *  Created on: Jun 25, 2019
 *      Author: wck
 */

#ifndef TIMER_H_
#define TIMER_H_

class Timer {
public:
	Timer();
	~Timer() = default;

	double GetTimeMilliSeconds();
	double GetTimeMilliSeconds(long trials);

private:
	double GetTime();
	double time_;
};

#endif /* TIMER_H_ */
