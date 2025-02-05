#pragma once

#include "../../basictypes.h"

#ifndef __LINUX__
# include <Windows.h>
#endif

namespace Network
{
	class Socket;

	namespace Protocol
	{
		class Prototype
		{
		public:
			virtual ~Prototype(void) {}

			virtual void	init(Socket const &socket, struct sockaddr_in&) = 0;

			virtual ulint	recive(char *buff, ulint size) = 0;
			virtual ulint	send(char const *buff, ulint size) = 0;

			//virtual void	setProtocol(Prototype &protocol) = 0;
		};
	}
}

#include "../Socket.h"
