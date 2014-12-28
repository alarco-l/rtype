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
			Content(llint second, llint milisecond);
			Content(Content const &copy);
			
			Content	&operator=(Content const &copy);

			llint	sec;
			llint	mili;
		};

		Time(Content const &content);

	public:
		Time(void);
		Time(Time const &copy);

		static Time	Millisecond(llint time);
		static Time	Second(llint time);
		static Time Curent(void);

		llint	millisecond(void) const;
		llint	second(void) const;
		float	asFloat() const;

		Time	&operator=(Time const &time);

		Time	operator-(Time const &other);
		Time	operator+(Time const &other);

	private:
		Content	_content;
	};

}
