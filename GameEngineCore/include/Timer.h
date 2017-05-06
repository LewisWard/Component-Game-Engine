/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
#pragma once
#include "Window.h"
#include <cstdint>

namespace GEC
{
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Timer that records the time taken in ms.
	/// \note  Can only be used on Windows Platofrms - uses Windows API functions.
	//----------------------------------------------------------------------------------------------------------------------
	class Timer
	{
	public:

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		//----------------------------------------------------------------------------------------------------------------------
		Timer();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Destructor
		//----------------------------------------------------------------------------------------------------------------------
		~Timer();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief start the timer
		//----------------------------------------------------------------------------------------------------------------------
		void start();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief end the timer
		//----------------------------------------------------------------------------------------------------------------------
		void stop();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief resets the timer
		//----------------------------------------------------------------------------------------------------------------------
		void reset();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief returns the time past since the start and end in milliseconds. Good for checking time past each frame.
		/// \return int64_t
		/// \note this is slower then elapsedTime, as the timer has to stop, compute time, then continue recording again.
		//----------------------------------------------------------------------------------------------------------------------
		int64_t checkElapsedTimeMS();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief computes the different between the start and end queries in milliseconds. Good for one off results, i.e. total execution time
		/// \return int64_t
		//----------------------------------------------------------------------------------------------------------------------
		int64_t elapsedTimeMS();


	private:
		LARGE_INTEGER m_start;
		LARGE_INTEGER m_end;
		LARGE_INTEGER m_clockFrequency;
	};
}
