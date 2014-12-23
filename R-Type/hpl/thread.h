#pragma once

#include <thread>

#include "basictypes.h"
#include "function.hpp"
#include "container.h"
#include "synchronous.h"

namespace hpl
{
	namespace Internal
	{
		class Thread
		{
		public:
			class Manager;

			class Instance
			{
			public:
				enum Status
				{
					Waiting,
					Running,
					Ended
				};

				Instance(::hpl::Internal::Thread::Manager &manager);
				~Instance(void);

				Status	status(void) const;
				void	start(void);
				void	stop(void);

			private:
				Status								_status;
				::hpl::Internal::Thread::Manager	&_manager;
				void								*_thread;
			};

			class CustomInstance
			{
			public:
				enum Status
				{
					Waitting,
					Running,
					Ended
				};

				CustomInstance(::hpl::Internal::Thread::Manager &manager, ::hpl::CallBack<CustomInstance&> call);
				~CustomInstance(void);

				Status	status(void) const;
				void	start(void);
				void	stop(void);

				Status								_status;
				::hpl::Internal::Thread::Manager	&_manager;

			private:
				::hpl::CallBack<CustomInstance&>	_call;
				void								*_thread;
			};


			class Manager
			{
			private:
				Manager(void);
				~Manager(void);

			public:
				static ::hpl::Internal::Thread::Manager	&instance(void);

				void	launch(::hpl::Call call);
				void	launchService(::hpl::CallBack<CustomInstance&> call);

				void	manage(void);

			private:
				static ::hpl::Internal::Thread::Manager	*_instance;

			public:
				::ullint	_nbThreadReady;
				::ullint	_nbThreadWaitting;

				::hpl::Synchronous::Locker	_locker;
				::hpl::Synchronous::Blocker	_blocker;

				::hpl::Container::Dynamic<::hpl::Internal::Thread::Instance*>		_threads;
				::hpl::Container::Dynamic<::hpl::Internal::Thread::CustomInstance*>	_services;
				::hpl::Container::Dynamic<::hpl::Call>								_calls;
			};

			Thread(void);
			~Thread(void);
		};
	}
}