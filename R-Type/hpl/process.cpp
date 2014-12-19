#include "process.hpp"
#include "exit.h"

#ifndef __LINUX__
# include <windows.h>
#endif // !__LINUX__

namespace hpl
{

	void	Process::atExit(::hpl::Call call){ ::hpl::Internal::AtExit::add(call); }
	int		Process::stop(void)
	{
		int ret = _main();
		::hpl::Internal::Thread::Manager::instance().manage();
		::hpl::Internal::AtExit::use();
		return (ret);
	}

	void	Process::async(::hpl::Call call) { ::hpl::Internal::Thread::Manager::instance().launch(call); }

	void	Process::sleep(::hpl::Time const &time)
	{
#ifndef __LINUX__
		Sleep((DWORD)time.millisecond());
#else
		usleep(time.millisecond() * 1000)
#endif // !__LINUX__
	}

	::hpl::Function<int(void)>	Process::_main;
}