#include "RFCManager.h"

RFCManager::RFCManager()
{
	_server = Network::Server::create(::hpl::bind(&RFCManager::onServerStart, this, ::hpl::Placeholder::_1));
}

RFCManager::~RFCManager()
{
}
//
//RFC		RFCManager::addRFC(RFC &rfc, Network::Socket &socket) {
//	_rfc[socket] = new RFC(socket);
//	return (_rfc[socket]);
//}

void	RFCManager::onReceiveEvent2(Network::Socket &socket)
{
	::hpl::Logger::out("Receive");
	char buff[1];
	int nb = socket.in().get(buff, 1);
	RFC::RecvCommand cmd = (RFC::RecvCommand)*(char *)(buff);
	//_rfc->recvCmd(cmd, socket);
}

void	RFCManager::onEndEvent2(Network::Socket const &socket)
{
	::hpl::Logger::out("End");
}

void	RFCManager::onConnectEvent(Network::Server &sever, Network::Socket &socket)
{
	::hpl::Logger::out("New client");
	//socket.onRecive(::hpl::bind(&onReceiveEvent2, ::hpl::Placeholder::_1));
	socket.onEnd(::hpl::bind(&RFCManager::onEndEvent2, this, ::hpl::Placeholder::_1));
	//RFC	*rfc = new RFC(socket);
}

void	RFCManager::onDisconnectEvent(Network::Server &server, Network::Socket const &socket)
{
	::hpl::Logger::out("Losing client");
}
void	RFCManager::onEndEvent(Network::Server const &server)
{
	::hpl::Logger::out("Stopping server");
}

void	RFCManager::onListenEvent(Network::Server &server)
{
	::hpl::Logger::out("Listen on 2222");
	_server->onDisconnect(::hpl::bind(&RFCManager::onDisconnectEvent,this, ::hpl::Placeholder::_1, ::hpl::Placeholder::_2));
	_server->onEnd(::hpl::bind(&RFCManager::onEndEvent, this, ::hpl::Placeholder::_1));
}

void	RFCManager::onServerStart(Network::Server &server)
{
	::hpl::Logger::out("Starting server");
	_server->onConnect(::hpl::bind(&RFCManager::onConnectEvent,this, ::hpl::Placeholder::_1, ::hpl::Placeholder::_2));
	_server->listen<Network::tcp::ip4>(2222, ::hpl::bind(&RFCManager::onListenEvent,this, ::hpl::Placeholder::_1));
}

