#include "None.h"

namespace Network
{
	namespace Protocol
	{
		None::None(void) : _socket(-1) {}
		None::~None(void) {}

		void	None::init(Socket const &socket) { _socket = socket.native(); }

		ulint	None::recive(char *buff, ulint size) { return (::recv(_socket, buff, size, 0)); }
		ulint	None::send(char const *buff, ulint size) { return (::send(_socket, buff, size, 0)); }

	}
}
