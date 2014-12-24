#include "Server.h"

#include "../process.hpp"

#include <iostream>
#include <cstring>

namespace Network
{
	Server::Server(::hpl::CallBack<Server&> onCreateEvent) : _running(false), _onCreateEvent(onCreateEvent)
	{
		::hpl::Process::service(::hpl::bind(&::Network::Server::start, this, ::hpl::Placeholder::_1));
	}
	Server::~Server(void) {}

	void	Server::start(::hpl::Internal::Thread::CustomInstance &instance)
	{
		try
		{
			instance._manager._locker.lock();
			++instance._manager._nbThreadWaitting;
			_mutex.lock();

#ifndef __LINUX__
# define socklen_t	int
			int	error;
			if ((error = WSAStartup(0x0202, &_wsaData)))
				throw (std::runtime_error("Network: WSAStartup fail"));
			if (_wsaData.wVersion != 0x0202)
				throw (std::runtime_error("Network: WSAStartup fail"));
#endif // !__LINUX__

			_running = true;

			FD_ZERO(&_fdRead);
			FD_ZERO(&_fdWrite);

			fd_set	fdRead;
			fd_set	fdWrite;
			struct timeval	timeVal = { 1, 0 };
			int		ret;

			struct sockaddr_in	cli_addr;
			socklen_t			size;
			ulint				socket;

			_onCreateEvent(*this);

			char	nullBuff[sizeof(fd_set)];
			std::memset(nullBuff, 0, sizeof(fd_set));

			while (_running && instance._status != ::hpl::Internal::Thread::CustomInstance::Status::Ended)
			{
				if (std::memcmp(&fdRead, nullBuff, sizeof(fd_set)))
				{
					if (instance._status == ::hpl::Internal::Thread::CustomInstance::Status::Waitting)
					{
						instance._status = ::hpl::Internal::Thread::CustomInstance::Status::Running;
						--instance._manager._nbThreadWaitting;
					}
				}
				else
				{
					if (instance._status == ::hpl::Internal::Thread::CustomInstance::Status::Running)
					{
						instance._status = ::hpl::Internal::Thread::CustomInstance::Status::Waitting;
						++instance._manager._nbThreadWaitting;
					}
				}
				instance._manager._locker.unlock();
				std::memcpy(&fdRead, &_fdRead, sizeof(fd_set));
				std::memcpy(&fdWrite, &_fdWrite, sizeof(fd_set));
				_mutex.unlock();
				timeVal.tv_sec = 1;
				ret = select(FD_SETSIZE, &fdRead, &fdWrite, NULL, &timeVal);
				_mutex.lock();
				if (!_running)
					break;
				for (auto it = _ports.begin(); it != _ports.end(); ++it)
					if (FD_ISSET(it->second->native(), &fdRead))
					{
						size = sizeof(cli_addr);
						std::memset((void*)&cli_addr, 0, sizeof(cli_addr));
						if ((socket = accept(it->second->native(), (struct sockaddr *)&cli_addr, &size)) == (ulint)-1)
							throw (std::runtime_error("Network: accept fail"));
						_clients[socket] = new Socket(socket, Socket::Type::Client);
						FD_SET(socket, &_fdRead);
						_onConnectEvent[_socketToCallback[it->second->native()]](*this, *_clients[socket]);
					}
				auto it = _clients.begin();
				while (it != _clients.end())
				{
					if (FD_ISSET(it->second->native(), &fdRead))
					{
						it->second->recive();
						if (!it->second->connected())
						{
							FD_CLR(it->second->native(), &_fdRead);
							FD_CLR(it->second->native(), &_fdWrite);
							delete (it->second);
							it = _clients.erase(it);
							continue;
						}
					}
					if (FD_ISSET(it->second->native(), &fdWrite))
					{
						it->second->send();
						FD_CLR(it->second->native(), &_fdWrite);
					}
					if (it->second->out().size())
						FD_SET(it->second->native(), &_fdWrite);
					++it;
				}
				instance._manager._locker.lock();
			}

			_mutex.unlock();
			instance._manager._locker.unlock();
		}

		catch (std::exception const &e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
			instance._manager._locker.unlock();
			throw;
		}
	}

	Server	*Server::create(::hpl::CallBack<Server&> onCreateEvent) { return (new Server(onCreateEvent)); }

	void	Server::onConnect(::hpl::CallBack<Server&, Socket&> onConnectEvent)
	{
		Lock	lock(_mutex);
		_onConnectEventDefault = onConnectEvent;
	}

	void	Server::onDisconnect(::hpl::CallBack<Server&, Socket const&> onDisconnectEvent)
	{
		Lock	lock(_mutex);
		_onDisconnectEvent = onDisconnectEvent;
	}
	void	Server::onEnd(::hpl::CallBack<Server const&> onEndEvent)
	{
		Lock	lock(_mutex);
		_onEndEvent = onEndEvent;
	}

	void	Server::listen(uint port, ::hpl::CallBack<Server&> onListenEvent, ::hpl::CallBack<Server&, Socket &> onConnectEvent)
	{

		Lock	lock(_mutex);

		sockaddr_in	addr;
		ulint	socket;

		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = htonl(INADDR_ANY);

		if ((socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == (ulint)-1)
			throw (std::runtime_error("Network: socket fail"));;
		if (bind(socket, (sockaddr*)&addr, sizeof(addr)) == -1)
			throw (std::runtime_error("Network: bind fail"));;
		::listen(socket, 5);

		FD_SET(socket, &_fdRead);
		_ports[port] = new Socket(socket, Socket::Type::Listen);
		_socketToCallback[socket] = port;
		_onConnectEvent[port] = onConnectEvent;
		onListenEvent(*this);
	}

	void	Server::listen(uint port, ::hpl::CallBack<Server&> onListenEvent) { listen(port, onListenEvent, _onConnectEventDefault); }

	void	Server::close(uint port)
	{
		Lock	lock(_mutex);
		auto it = _ports.find(port);
		if (it != _ports.end())
		{
			FD_CLR(it->second->native(), &_fdRead);
			delete (it->second);
			_ports.erase(it);
		}
	}
	void	Server::close(void)
	{
		Lock	lock(_mutex);

		auto	it = _clients.begin();
		while (it != _clients.end())
		{
			FD_CLR(it->second->native(), &_fdRead);
			FD_CLR(it->second->native(), &_fdWrite);
			delete it->second;
			it = _clients.erase(it);
		}
		it = _ports.begin();
		while (it != _ports.end())
		{
			FD_CLR(it->second->native(), &_fdRead);
			delete (it->second);
			it = _ports.erase(it);
		}
		_running = false;
		_onEndEvent(*this);
#ifndef __LINUX__
		WSACleanup();
#endif // !__LINUX__
	}
}

