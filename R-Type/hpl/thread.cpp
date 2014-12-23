#include "thread.h"
#include "process.hpp"

#include <windows.h>

ulint __stdcall	threadFunc(::hpl::Internal::Thread::Instance *myself)
{
	myself->start();
	return (0);
}

ulint __stdcall	threadCustomFunc(::hpl::Internal::Thread::CustomInstance *myself)
{
	myself->start();
	return (0);
}

namespace hpl
{
	namespace Internal
	{

		Thread::Instance::Instance(::hpl::Internal::Thread::Manager &manager)
			: _status(Status::Waiting), _manager(manager)
		{
			_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&threadFunc, this, 0, NULL);
		}

		Thread::Instance::~Instance(void)
		{
			stop();
			if (_thread)
				WaitForMultipleObjects(1, &_thread, TRUE, INFINITE);
		}

		void	Thread::Instance::start(void)
		{
			_manager._locker.lock();
			++_manager._nbThreadReady;
			while (_status != Status::Ended)
			{
				if (_manager._calls.empty())
					_manager._blocker.lock();
				else
				{
					::hpl::Call	call = _manager._calls.front();
					_manager._calls.pop_front();
					Status	last = _status;
					_status = Status::Running;
					--_manager._nbThreadReady;
					_manager._locker.unlock();
					call();
					_manager._locker.lock();
					++_manager._nbThreadReady;
					_status = last;
				}
			}
			_manager._locker.unlock();
		}

		Thread::Instance::Status	Thread::Instance::status(void) const { return (_status); }

		void	Thread::Instance::stop(void)
		{
			_manager._locker.lock();
			_status = Status::Ended;
			_manager._locker.unlock();
		}

		Thread::CustomInstance::CustomInstance(::hpl::Internal::Thread::Manager &manager, ::hpl::CallBack<CustomInstance&> call)
			: _status(Status::Waitting), _call(call), _manager(manager)
		{
			_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&threadCustomFunc, this, 0, NULL);
		}

		Thread::CustomInstance::~CustomInstance(void)
		{
			stop();
			if (_thread)
				WaitForMultipleObjects(1, &_thread, TRUE, INFINITE);
		}

		void	Thread::CustomInstance::start(void)
		{
			_call(*this);
		}

		Thread::CustomInstance::Status	Thread::CustomInstance::status(void) const { return (_status); }

		void	Thread::CustomInstance::stop(void)
		{
			_manager._locker.lock();
			_status = Status::Ended;
			_manager._locker.unlock();
		}

		::hpl::Internal::Thread::Manager	&Thread::Manager::instance(void) { return (*_instance); }

		Thread::Manager::Manager(void) : _nbThreadReady(0), _nbThreadWaitting(0), _blocker(_locker) {}

		void	Thread::Manager::manage(void)
		{
			_locker.lock();
			while (_nbThreadReady != _threads.size() || _nbThreadWaitting != _services.size())
			{
				_locker.unlock();
				Process::sleep(Time::Millisecond(100));
				_locker.lock();
			}
			for (auto it = _threads.begin(); it != _threads.end(); ++it)
				(*it)->stop();
			_locker.unlock();
			_blocker.unlockAll();
			for (auto it = _threads.begin(); it != _threads.end(); ++it)
				delete (*it);
			_threads.clear();
		}

		Thread::Manager::~Manager(void) {}

		void	Thread::Manager::launch(::hpl::Call call)
		{
			_locker.lock();
			if (_threads.size() < 10)
				while (_threads.size() < 10)
					_threads.push_back(new Thread::Instance(*this));
			else if (!_nbThreadReady)
				_threads.push_back(new Thread::Instance(*this));
			_calls.push_back(call);
			_blocker.unlock();
			_locker.unlock();
		}

		void	Thread::Manager::launchService(::hpl::CallBack<CustomInstance&> call)
		{
			_locker.lock();
			_services.push_back(new Thread::CustomInstance(*this, call));
			_locker.unlock();
		}

		::hpl::Internal::Thread::Manager	*Thread::Manager::_instance = new ::hpl::Internal::Thread::Manager;
	}
}