#include "times.h"

#include <cstring>

#ifndef __LINUX__
# include <Windows.h>
#endif

namespace hpl
{
	Time::Content::Content(void) : sec(0), mili(0) {}
	Time::Content::Content(ullint second, ullint milisecond) : sec(second), mili(milisecond) {}
	Time::Content::Content(Content const &copy) : sec(copy.sec), mili(copy.mili) {}

	Time::Content	&Time::Content::operator=(Content const &copy)
	{
		sec = copy.sec;
		mili = copy.mili;
		return (*this);
	}

	Time::Time(Content const &content) : _content(content) {}

	Time::Time(void) {}
	Time::Time(Time const &copy) : _content(copy._content) {}

	Time	Time::Millisecond(ullint time) { return (Time(Content(time / 1000, time - time / 1000 * 1000))); }
	Time	Time::Second(ullint time) { return (Time(Content(time, 0))); }
	Time	Time::Curent(void)
	{
		SYSTEMTIME	time;
		GetSystemTime(&time);
		return (Time(Content(time.wHour * 3600 + time.wMinute * 60 + time.wSecond, time.wMilliseconds)));
	}

	ullint	Time::millisecond(void) const { return (_content.sec * 1000 + _content.mili); }
	ullint	Time::second(void) const { return (_content.sec + _content.mili / 1000); }

	Time	&Time::operator=(Time const &other) { _content.sec = other._content.sec; _content.mili = other._content.mili; return (*this); }
	Time	Time::operator-(Time const &other) { return (Time(Content(_content.sec - other._content.sec, _content.mili - other._content.mili))); }
	Time	Time::operator+(Time const &other) { return (Time(Content(_content.sec - other._content.sec, _content.mili - other._content.mili))); }
}