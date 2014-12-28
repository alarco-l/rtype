#pragma once

namespace Network
{
	enum
	{
		_tcp		= 0,
		_udp		= 1
	};
	enum
	{
		_ip4		= 0
	};
	enum
	{
		tcp_ip4		= _tcp + _ip4,
		udp_ip4		= _udp + _ip4
	};
	namespace tcp
	{
		enum
		{
			ip4		= tcp_ip4
		};
	}
	namespace udp
	{
		enum
		{
			ip4		= udp_ip4
		};
	}
}