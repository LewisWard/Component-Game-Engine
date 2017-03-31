// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 31/03/2016
#include "Timer.h"

namespace GEC
{
	Timer::Timer()
	{
		start();
	}

	Timer::~Timer()
	{

	}

	void Timer::start() 
	{ 
		QueryPerformanceFrequency(&m_clockFrequency);
		QueryPerformanceCounter(&m_start);
	}

	void Timer::stop() 
	{
		QueryPerformanceCounter(&m_end);
	}

	void Timer::reset()
	{
		QueryPerformanceCounter(&m_start);
	}

	int64_t Timer::checkElapsedTimeMS()
	{
		stop();
		int64_t time = (m_end.QuadPart - m_start.QuadPart) * 1000.0 / m_clockFrequency.QuadPart;

		return time;
	}

	int64_t Timer::elapsedTimeMS()
	{ 
		return (m_end.QuadPart - m_start.QuadPart) * 1000.0 / m_clockFrequency.QuadPart;
	}
}
