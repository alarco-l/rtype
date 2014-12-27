#pragma once

namespace Network
{
	enum
	{
		tcp_ip4,
		udp_ip4
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