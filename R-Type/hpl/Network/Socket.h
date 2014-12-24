#pragma once

#ifndef __LINUX__
# include <Windows.h>
#else
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
#endif // !__LINUX__

#include "../basictypes.h"
#include "../function.hpp"
#include "../buffer.h"
#include "../utils.hpp"
#include "../synchronous.h"

namespace Network
{
	class Socket;
}

#include "Protocol/None.h"

namespace Network
{
	namespace Protocol
	{
		class None : public Prototype
		{
		public:
			None(void);
			~None(void);

			void	init(Socket const &socket);

			ulint	recive(char *buff, ulint size);
			ulint	send(char const *buff, ulint size);

		private:
			ulint	_socket;
		};
	}


	class Socket
	{
	public:
		enum Type
		{
			Listen,
			Connection,
			Client
		};

		static int	close(ulint socket);

		Socket(::ulint socket, Socket::Type type);
		~Socket(void);

		ulint			native(void) const;
		Socket::Type	type(void) const;

		template <typename protocol> void	useProtocol(void)
		{
			_mutex.lock();
			if (!::hpl::Inheritance::IsInherit<Protocol::Prototype, protocol>::value
				|| ::hpl::Inheritance::IsSame<Protocol::Prototype, protocol>::value)
			{
				_mutex.unlock();
				throw (std::runtime_error("Network: Socket: useProtocol with bad protocol"));
			}
			if (this->_protocol)
				delete _protocol;
			_protocol = new protocol;
			_protocol->init(*this);
			_mutex.unlock();
		}

		void	recive(void);
		void	send(void);

		void	onRecive(::hpl::CallBack<Socket&> onReciveEvent);
		void	onEnd(::hpl::CallBack<Socket const&> onEndEvent);

		::hpl::Buffer	&in(void);
		::hpl::Buffer	&out(void);

		void	close(void);
		bool	connected(void);

	private:
		ulint			_socket;
		Socket::Type	_type;

		bool	_connected;

		::hpl::CallBack<Socket&>		_onReciveEvent;
		::hpl::CallBack<Socket const&>	_onEndEvent;

		Protocol::Prototype				*_protocol;

		::hpl::Buffer					_readStream;
		::hpl::Buffer					_writeStream;
		ulint							_writeLength;

		::hpl::Synchronous::Locker		_mutex;
		
	Socket(Socket const &copy) : _protocol(NULL) {(void)copy;}
		Socket	&operator=(Socket const &copy) { (void)copy; return (*this); }
	};
}

