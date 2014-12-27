#include "clock.h"

namespace hpl
{
	Clock::Clock(void) { reset(); }
	Clock::Clock(Clock const &copy) { this->operator=(copy); }
	Clock::Clock(Time const & copy) { this->operator=(copy); }
	Clock::~Clock(void) {}

	Clock	&Clock::operator=(Clock const &copy) { _time = copy._time; return (*this); }
	Clock	&Clock::operator=(Time const &copy) { _time = copy; return (*this); }

	void	Clock::reset(void) { _time = Time::Curent(); }
	Time	Clock::getElapsedTime(void) const { return (Time::Curent() - _time); }
}