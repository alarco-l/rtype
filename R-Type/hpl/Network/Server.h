#pragma once

#ifndef __LINUX__
# include <Winsock.h>
#endif // !__LINUX__

#include "../basictypes.h"
#include "../function.hpp"
#include "../process.hpp"
#include "../synchronous.h"
#include "../container.h"
#include "Socket.h"
#include "network.h"

namespace Network
{
	class Server
	{
	public:
		enum Error
		{
			None
		};

	protected:
		Server(::hpl::CallBack<Server&> onCreateEvent);

	public:
		~Server(void);

		static Server	*create(::hpl::CallBack<Server&> onCreateEvent);

		void	Server::start(::hpl::Internal::Thread::CustomInstance &instance);
		
		void	onConnect(::hpl::CallBack<Server&, Socket&> onConnectEvent);
		void	onDisconnect(::hpl::CallBack<Server&, Socket const&> onDisconnectEvent);
		void	onEnd(::hpl::CallBack<Server const&> onEndEvent);

		template <int type> void	listen(uint port, ::hpl::CallBack<Server&> onListenEvent, ::hpl::CallBack<Server&, Socket &> onConnectEvent)
		{

			_mutex.lock();

			sockaddr_in	addr;
			ulint	socket;

			std::memset(&addr, 0, sizeof(addr));
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
			addr.sin_addr.s_addr = htonl(INADDR_ANY);
			
			int proType = (type & 0x1 ? SOCK_DGRAM : SOCK_STREAM);
			int protocol = (type & 0x1 ? IPPROTO_UDP : IPPROTO_TCP);
			_protocol = type;

			if ((socket = ::socket(AF_INET, proType, protocol)) == (ulint)-1)
				throw (std::runtime_error("Network: socket fail"));;
			if (bind(socket, (sockaddr*)&addr, sizeof(addr)) == -1)
				throw (std::runtime_error("Network: bind fail"));;
			::listen(socket, 5);

			FD_SET(socket, &_fdRead);
			_ports[port] = new Socket(socket, (type & 0x1 ? Socket::Type::udpListen : Socket::Type::Listen));
			_socketToCallback[socket] = port;
			_onConnectEvent[port] = onConnectEvent;
			onListenEvent(*this);
			_mutex.unlock();
		}

		template <int type> void	listen(uint port, ::hpl::CallBack<Server&> onListenEvent) { listen<type>(port, onListenEvent, _onConnectEventDefault); }

		void	close(uint port);
		void	close(void);

	private:
		std::thread			_thread;

	protected:
		typedef ::hpl::Container::Associative<ulint, Socket *>								SocketTank;
		typedef ::hpl::Container::Associative<ulint, ::hpl::CallBack<Server&, Socket &> >	CallbackTank;
		typedef	::hpl::Container::Associative<ulint, ulint>									SocketToCallback;

		::hpl::Synchronous::Locker	_mutex;
		bool						_running;

		CallbackTank							_onConnectEvent;
		::hpl::CallBack<Server&, Socket&>		_onConnectEventDefault;
		::hpl::CallBack<Server&>				_onCreateEvent;
		SocketToCallback						_socketToCallback;
		::hpl::CallBack<Server&, Socket const&>	_onDisconnectEvent;
		::hpl::CallBack<Server const&>			_onEndEvent;

		fd_set			_fdRead;
		fd_set			_fdWrite;
#ifndef __LINUX__
		WSAData			_wsaData;
#endif // !__LINUX__

		SocketTank		_ports;
		SocketTank		_clients;
		int				_protocol;
	};
}
