#pragma once

#include "times.h"

namespace hpl
{
	class Clock
	{
		Time		_time;

	public:
		Clock(void);
		Clock(Clock const &copy);
		Clock(Time const & copy);
		~Clock(void);

		Clock	&operator=(Clock const &copy);
		Clock	&operator=(Time const &copy);

		void	reset(void);
		Time	getElapsedTime(void) const;
	};
}
