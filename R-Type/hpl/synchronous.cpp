#include "synchronous.h"

#include <Windows.h>

#include "exceptions.h"

namespace hpl
{
	namespace Synchronous
	{
		Locker::Locker(void)
		{
			InitializeCriticalSection(&_section);
		}
		Locker::~Locker(void) {}

		void	Locker::lock(void) const
		{
			EnterCriticalSection(const_cast<LPCRITICAL_SECTION>(&_section));
		}
		void	Locker::unlock(void) const
		{
			LeaveCriticalSection(const_cast<LPCRITICAL_SECTION>(&_section));
		}

		Blocker::Blocker(Locker &locker) : _locker(locker)
		{
			InitializeConditionVariable(&_condition);
		}
		Blocker::~Blocker(void) {}

		void	Blocker::lock(void)
		{
			SleepConditionVariableCS(&_condition, &_locker._section, INFINITE);
		}
		void	Blocker::unlock(void)
		{
			_locker.lock();
			WakeConditionVariable(&_condition);
			_locker.unlock();
		}
		void	Blocker::unlockAll(void)
		{
			_locker.lock();
			WakeAllConditionVariable(&_condition);
			_locker.unlock();
		}
	}
}