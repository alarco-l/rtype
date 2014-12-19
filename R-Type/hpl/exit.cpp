#include "exit.h"

namespace hpl
{
	namespace Internal
	{
		void	AtExit::add(::hpl::Call call)
		{
			_instance->_locker.lock();
			_instance->_calls.push_back(call);
			_instance->_locker.unlock();
		}
		void	AtExit::use(void)
		{
			_instance->_locker.lock();
			auto it = _instance->_calls.begin();
			while (it != _instance->_calls.end())
			{
				(*it)();
				it = _instance->_calls.erase(it);
			}
			_instance->_locker.unlock();
		}

		::hpl::Internal::AtExit	*AtExit::_instance = new ::hpl::Internal::AtExit;
	}
}