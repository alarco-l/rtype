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

		void	listen(uint port, ::hpl::CallBack<Server&> onListenEvent);
		void	listen(uint port, ::hpl::CallBack<Server&> onListenEvent, ::hpl::CallBack<Server&, Socket&> onConnectEcent);

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
	};
}
