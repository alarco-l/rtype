#pragma once

#include <stdexcept>

#include "basictypes.h"
#include "function.hpp"
#include "thread.h"
#include "times.h"

int hpl_main(int, char *[], char *[]);

namespace hpl
{
	class Process
	{
	public:
		static void	start(int argc, char *argv[], char *env[]) { _main = ::hpl::bind(&::hpl_main, argc, argv, env); }
		static int	stop(void);

		static void	atExit(::hpl::Call call);

		static void	async(::hpl::Call call);

		static void	sleep(::hpl::Time const &time);

	private:
		static ::hpl::Function<int(void)>	_main;
	};
}