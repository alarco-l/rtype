#pragma once

#include <string>

#include "../basictypes.h"
#include "../function.hpp"
#include "../process.hpp"
#include "../container.h"
#include "../synchronous.h"
#include "Socket.h"
#include "network.h"

namespace Network
{
	class Client
	{
	public:
		struct Config
		{
			Config(std::string Addr, uint Port) : addr(Addr), port(Port) {}
			Config(uint Port) : addr("127.0.0.1"), port(Port) {}

			std::string	addr;
			uint		port;
		};

	protected:
		Client(ulint socket, ::hpl::CallBack<Client &> onConnectEvent);
		Client(ulint socket, ::hpl::CallBack<Client &> onConnectEvent, sockaddr_in &);

	public:
		~Client(void);

		template <int protocol> static Client	*connect(Client::Config &config, ::hpl::CallBack<Client &> onConnectEvent)
		{
			sockaddr_in	addr;
			Client		*client;
			if (protocol & 0x1)
				client = new Client(Client::Manager::getInstance()->connect(config, protocol, addr), onConnectEvent, addr);
			else
				client = new Client(Client::Manager::getInstance()->connect(config, protocol, addr), onConnectEvent);
			Client::Manager::getInstance()->manage(*client);
			return (client);
		}

		Socket	socket;

	private:

		::hpl::Synchronous::Locker	_mutex;

		class Manager
		{
		private:
			Manager(void);
			~Manager(void);

		public:
			static Manager	*getInstance(void);

			ulint			connect(Config &config, int protocol, sockaddr_in&);

			void			manage(Client &client);
			void			forget(Client &client);

			void			start(::hpl::Internal::Thread::CustomInstance &);

		private:
			typedef ::hpl::Container::Associative<ulint, Client*>	SocketTank;

			::hpl::Synchronous::Locker	_mutex;

			SocketTank	_sockets;
			fd_set		_fdRead;
			fd_set		_fdWrite;

			static Manager	*_instance;

#ifndef __LINUX__
			WSAData		_wsaData;
#endif // !__LINUX__
		};
	};
}
