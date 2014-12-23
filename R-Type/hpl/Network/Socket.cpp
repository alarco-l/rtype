#include "Socket.h"

#ifdef __LINUX__
# include <unistd.h>
#endif // !__LINUX__

#include "../utils.hpp"

namespace Network
{
	int	Socket::close(::ulint socket)
	{
#ifndef __LINUX__
		return (::closesocket(socket));
#else
		return (::close(socket));
#endif // !__LINUX__
	}

  Socket::Socket(ulint socket, Socket::Type type) : _socket(socket), _type(type), _connected(socket != (ulint)-1), _protocol(NULL)
	{
		useProtocol<Protocol::None>();
	}
	Socket::~Socket(void) { close(); }
	
	ulint			Socket::native(void) const { return (_socket); }
	Socket::Type	Socket::type(void) const { return (_type); }

	void	Socket::recive(void)
	{
		Lock	lock(_mutex);
		char	buff[255];
		ulint	size;

		size = _protocol->recive(buff, sizeof(buff));
		switch (size)
		{
		case (ulint)-1:
		case 0:
			close();
			break;
		default:
			_readStream.write(buff, size);
			_onReciveEvent(*this);
		}

	}
	void	Socket::send(void)
	{
		Lock	lock(_mutex);
		ulint length = _writeStream.size();
		if (!length)
			return;
		char *buffer = new char[length];
		_writeStream.get(buffer, length);
		_protocol->send(buffer, length);
		delete []buffer;
	}

	void	Socket::onRecive(::hpl::CallBack<Socket&> onReciveEvent)
	{
		Lock	lock(_mutex);
		_onReciveEvent = onReciveEvent;
		if (_readStream.size())
			_onReciveEvent(*this);
	}

	void	Socket::onEnd(::hpl::CallBack<Socket const&> onEndEvent)
	{
		Lock	lock(_mutex);
		_onEndEvent = onEndEvent;
	}
	::hpl::Buffer	&Socket::in(void)
	{
		Lock	lock(_mutex);
		return (_readStream);
	}
	::hpl::Buffer	&Socket::out(void)
	{
		Lock	lock(_mutex);
		return (_writeStream);
	}

	void	Socket::close(void)
	{
		Lock	lock(_mutex);

		if (_connected)
		{
			_writeStream.clear();
			_readStream.clear();
			if (_onEndEvent)
				_onEndEvent(*this);
			if (_socket != (ulint)-1)
				close(_socket);
			_connected = false;
			if (_protocol)
			{
				delete _protocol;
				_protocol = NULL;
			}
		}
	}

	bool	Socket::connected(void)
	{
		Lock	lock(_mutex);
		return (_connected);
	}
}
