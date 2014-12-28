#pragma once

#include <Windows.h>
#include "basictypes.h"

namespace hpl
{
	namespace Synchronous
	{
		class Locker
		{
		public:
			CRITICAL_SECTION	_section;

			Locker(void);
			~Locker(void);

			void	lock(void) const;
			void	unlock(void) const;
		};

		class Blocker
		{
			CONDITION_VARIABLE	_condition;
			Locker				&_locker;

		public:
			Blocker(Locker &locker);
			~Blocker(void);

			void	lock(void);
			void	unlock(void);
			void	unlockAll(void);
		};
	}
}