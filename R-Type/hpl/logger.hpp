#pragma once

#include <iostream>
#include "synchronous.h"

namespace hpl
{
	class Logger
	{
		static Logger	*_instance;

		hpl::Synchronous::Locker	_locker;
	public:
		template <typename Type> static void	err(Type const &error)
		{
			_instance->_locker.lock();
			::std::cerr << error << std::endl;
			_instance->_locker.unlock();
		}
		template <typename Type> static void	out(Type const &error)
		{
			_instance->_locker.lock();
			::std::cout << error << std::endl;
			_instance->_locker.unlock();
		}
	};
}

