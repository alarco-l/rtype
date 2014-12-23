#include "Client.h"

#include "process.h"

#include <cstring>

namespace Network
{

	Client::Client(ulint socket, ::hpl::CallBack<Client &> onConnectEvent) : socket(socket, Socket::Type::Connection)
	{
		Lock	lock(_mutex);
		onConnectEvent(*this);
	}

	Client::~Client(void)
	{
		Lock	lock(_mutex);
		Client::Manager::getInstance()->forget(*this);
	}

	Client	*Client::connect(Client::Config &config, ::hpl::CallBack<Client &> onConnectEvent)
	{
		Client		*client = new Client(Client::Manager::getInstance()->connect(config), onConnectEvent);
		Client::Manager::getInstance()->manage(*client);
		return (client);
	}


	Client::Manager::Manager(void)
	{
#ifndef __LINUX__
		int	error;
		if ((error = WSAStartup(0x0202, &_wsaData)))
			throw (std::runtime_error("Network: WSAStartup fail"));
		if (_wsaData.wVersion != 0x0202)
			throw (std::runtime_error("Network: WSAStartup fail"));
#endif // !__LINUX__
	}

	Client::Manager::~Manager(void)
	{
#ifndef __LINUX__
		WSACleanup();
#endif // !__LINUX__
	}

	Client::Manager	*Client::Manager::getInstance(void) { return (_instance); }
	Client::Manager	*Client::Manager::_instance = new Client::Manager;

	ulint			Client::Manager::connect(Client::Config &config)
	{
		ulint		socket;
		sockaddr_in	sin;

		if ((socket = ::socket(AF_INET, SOCK_STREAM, 0)) == (ulint)-1)
			throw (std::runtime_error("Network: socket fail"));
		sin.sin_addr.s_addr = inet_addr(config.addr.c_str());
		sin.sin_family = AF_INET;
		sin.sin_port = htons(config.port);
		if (::connect(socket, (sockaddr *)&sin, sizeof(sin)))
			throw (std::runtime_error("Network: connect fail"));
		return (socket);
	}

	void		Client::Manager::manage(Client &client)
	{
		_mutex.lock();
		if (!_sockets.size())
		{
			FD_ZERO(&_fdRead);
			FD_ZERO(&_fdWrite);
			FD_SET(client.socket.native(), &_fdRead);
			FD_SET(client.socket.native(), &_fdWrite);
			_sockets[client.socket.native()] = &client;

			_thread = std::thread([this] {
				_mutex.lock();

				fd_set	fdRead;
				fd_set	fdWrite;
				struct timeval	timeVal = { 0, 500 };
				int		ret;

				while (_sockets.size())
				{
					std::memcpy(&fdRead, &_fdRead, sizeof(fd_set));
					std::memcpy(&fdWrite, &_fdWrite, sizeof(fd_set));
					_condition.notify_all();
					_mutex.unlock();
					timeVal.tv_usec = 500;
					ret = select(FD_SETSIZE, &fdRead, &fdWrite, NULL, &timeVal);
					if (_sockets.empty())
						break;
					_mutex.lock();
					auto it = _sockets.begin();
					while (it != _sockets.end())
					{
						if (!it->second->socket.connected())
						{
							FD_CLR(it->second->socket.native(), &_fdRead);
							FD_CLR(it->second->socket.native(), &_fdWrite);
							it = _sockets.erase(it);
						}
						else
						{
							if (FD_ISSET(it->second->socket.native(), &fdRead))
								it->second->socket.recive();
							if (FD_ISSET(it->second->socket.native(), &fdWrite))
							{
								it->second->socket.send();
								FD_CLR(it->second->socket.native(), &_fdWrite);
							}
							if (it->second->socket.out().size())
								FD_SET(it->second->socket.native(), &_fdWrite);
							++it;
						}
					}
				}
				_mutex.unlock();
			});
			_mutex.unlock();
			std::unique_lock<std::mutex>	lock(_conditionMutex);
			_condition.wait(lock);
			//Process::atExit([this]{
			//	if (_thread.joinable())
			//		_thread.join();
			//});

			//Process::onExitEvent([this]{
			//	_mutex.lock();
			//	for (auto it = _sockets.begin(); it != _sockets.end(); ++it)
			//		it->second->socket.close();
			//	_sockets.clear();
			//	_mutex.unlock();
			//});

		}
		else
		{
			FD_SET(client.socket.native(), &_fdRead);
			_sockets[client.socket.native()] = &client;
			_mutex.unlock();
		}
	}

	void	Client::Manager::forget(Client &client)
	{
		FD_CLR(client.socket.native(), &_fdRead);
		FD_CLR(client.socket.native(), &_fdWrite);
		_sockets.erase(client.socket.native());
	}
}
