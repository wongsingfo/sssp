/*
 * timer.cc
 *
 *  Created on: Jun 25, 2019
 *      Author: wck
 */

#include "timer.h"

#include <cstdlib>
#include <sys/time.h>     
#include <sys/resource.h>
#include <unistd.h>

double Timer::GetTimeMilliSeconds(long trials) {
	return GetTimeMilliSeconds() / trials;
}
double Timer::GetTimeMilliSeconds() {
	return (GetTime() - time_) * 1000;
}

// unit: us
double Timer::GetTime()
{
	struct rusage r;
	getrusage(0, &r);
	return (double)(r.ru_utime.tv_sec+r.ru_utime.tv_usec/(double)1000000);
}

Timer::Timer() : time_(GetTime()) {
}

