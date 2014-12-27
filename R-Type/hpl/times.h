#pragma once

#include "basictypes.h"
#include <time.h>

namespace hpl
{
	class Time
	{
		struct Content
		{
			Content(void);
			Content(ullint second, ullint milisecond);
			Content(Content const &copy);
			
			Content	&operator=(Content const &copy);

			ullint	sec;
			ullint	mili;
		};

		Time(Content const &content);

	public:
		Time(void);
		Time(Time const &copy);

		static Time	Millisecond(ullint time);
		static Time	Second(ullint time);
		static Time Curent(void);

		ullint	millisecond(void) const;
		ullint	second(void) const;

		Time	&operator=(Time const &time);

		Time	operator-(Time const &other);
		Time	operator+(Time const &other);

	private:
		Content	_content;
	};

}
