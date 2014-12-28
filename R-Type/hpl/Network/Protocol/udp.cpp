#include "Prototype.h"

#include <cstring>

namespace Network
{
	namespace Protocol
	{
		udp::udp(void) : _socket(-1) {}
		udp::~udp(void) {}

		void	udp::init(Socket const &socket, struct sockaddr_in &cli_addr)
		{
			_socket = socket._socket;
			std::memcpy(&_cli_addr, &cli_addr, sizeof(cli_addr));
		}

		ulint	udp::recive(char *buff, ulint size)
		{
			int	s = sizeof(_cli_addr);
			return (recvfrom(_socket, buff, size, 0, (struct sockaddr *)&_cli_addr, &s));
		}

		ulint	udp::send(char const *buff, ulint size) { return (sendto(_socket, buff, size, 0, (struct sockaddr *)&_cli_addr, sizeof(_cli_addr))); }

	}
}
