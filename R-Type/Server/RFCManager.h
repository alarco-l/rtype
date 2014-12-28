# pragma once

# include "RFC.h"
# include "hpl.h"
# include "Network/Server.h"

class RFCManager
{
public:
	RFCManager();
	~RFCManager();
	//void		addRFC(RFC &rfc);
	void		onReceiveEvent2(Network::Socket &socket);
	void		onEndEvent2(Network::Socket const &socket);
	void		onConnectEvent(Network::Server &server, Network::Socket &socket);
	void		onDisconnectEvent(Network::Server &server, Network::Socket const &socket);
	void		onEndEvent(Network::Server const&);
	void		onListenEvent(Network::Server &server);
	void		onServerStart(Network::Server &server);

	std::vector<RFC *>	rfc;

private:
	Network::Server		*_server;
};
