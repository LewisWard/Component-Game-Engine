/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
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
