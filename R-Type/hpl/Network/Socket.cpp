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
		this->useProtocol<Protocol::None>();
	}
	Socket::Socket(ulint socket, Socket::Type type, struct sockaddr_in &cli_addr) : _socket(socket), _type(type), _connected(socket != (ulint)-1), _protocol(NULL)
	{
		std::memcpy(&_cli_addr, &cli_addr, sizeof(cli_addr));
		this->useProtocol<Protocol::udp>();
	}
	Socket::~Socket(void)
	{
		close();
		if (_protocol)
		{
			delete _protocol;
			_protocol = NULL;
		}
	}
	
	ulint			Socket::native(void) const { return (_type != udpClient ? _socket : _cli_addr.sin_port); }
	Socket::Type	Socket::type(void) const { return (_type); }

	void	Socket::recive(::hpl::Buffer &buffer)
	{
		_mutex.lock();
		_readStream.write(buffer);
		if (_onReciveEvent)
			_onReciveEvent(*this);
		_mutex.unlock();
	}
	void	Socket::recive(void)
	{
		_mutex.lock();
		char	buff[255];
		ulint	size;


		size = _protocol->recive(buff, sizeof(buff));
		switch (size)
		{
		case (ulint)-1:
			if (_cli_addr.sin_port != _socket)
				break;
		case 0:
			close();
			break;
		default:
			_readStream.write(buff, size);
			if (_onReciveEvent)
				_onReciveEvent(*this);
		}
		_mutex.unlock();
	}
	void	Socket::send(void)
	{
		_mutex.lock();
		ulint length = _writeStream.size();
		if (!length)
		{
			_mutex.unlock();
			return;
		}
		char *buffer = new char[length];
		_writeStream.get(buffer, length);
		_protocol->send(buffer, length);
		delete []buffer;
		_mutex.unlock();
	}

	void	Socket::onRecive(::hpl::CallBack<Socket&> onReciveEvent)
	{
		_mutex.lock();
		_onReciveEvent = onReciveEvent;
		if (_readStream.size())
		{
			_mutex.unlock();
			_onReciveEvent(*this);
		}
		else
			_mutex.unlock();
	}

	void	Socket::onEnd(::hpl::CallBack<Socket const&> onEndEvent)
	{
		_mutex.lock();
		_onEndEvent = onEndEvent;
		_mutex.unlock();
	}
	::hpl::Buffer	&Socket::in(void) { return (_readStream); }
	::hpl::Buffer	&Socket::out(void) { return (_writeStream); }

	void	Socket::close(void)
	{
		_mutex.lock();

		if (_connected)
		{
			//_writeStream.clear();
			//_readStream.clear();
			if (_onEndEvent)
				_onEndEvent(*this);
			//if (_socket != (ulint)-1)
				close(_socket);
			_connected = false;
		}
		_mutex.unlock();
	}

	bool	Socket::connected(void) { return (_connected); }
}
