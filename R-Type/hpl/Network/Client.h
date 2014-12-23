#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <map>

#include "../basictypes.h"
#include "../function.hpp"
#include "Socket.h"

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

	public:
		~Client(void);

		static Client	*connect(Config &config, ::hpl::CallBack<Client &> onConnectEvent);

		Socket	socket;

	private:
		typedef std::lock_guard<std::recursive_mutex>	Lock;

		std::recursive_mutex	_mutex;

		class Manager
		{
		private:
			Manager(void);
			~Manager(void);

		public:
			static Manager	*getInstance(void);

			ulint			connect(Config &config);

			void			manage(Client &client);
			void			forget(Client &client);

		private:
			typedef std::lock_guard<std::recursive_mutex>	Lock;
			typedef std::map<ulint, Client*>	SocketTank;

			std::thread				_thread;
			std::recursive_mutex	_mutex;

			std::mutex				_conditionMutex;
			std::condition_variable	_condition;

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
