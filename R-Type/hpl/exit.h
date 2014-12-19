#pragma once

#include "container.h"
#include "function.hpp"
#include "synchronous.h"

namespace hpl
{
	namespace Internal
	{
		class AtExit
		{
		public:
			static void	add(::hpl::Call call);
			static void	use(void);

		private:
			::hpl::Container::Dynamic<::hpl::Call>	_calls;
			::hpl::Synchronous::Locker	_locker;

			static ::hpl::Internal::AtExit	*_instance;
		};
	}
}