#ifndef TIMER_H
#define TIMER_H
#include <iostream>
#include <time.h>
#include <stdexcept>
#include <iomanip>
#include <chrono>
class Timer
{
private:
	std::chrono::system_clock::time_point m_start, m_stop;
	bool running;
public:
	void start();
	void stop();
	Timer();
	friend std::ostream& operator<<(std::ostream& ostm, const Timer& timer);
	double getTime();
};
#endif