#include <SFML/Graphics.hpp>

#include "World.h"
#include "Systems.h"
#include "ComponentFactory.h"
#include "ResourceManager.h"
#include "Game.h"

#include "hpl.h"
#include "Network/Server.h"
//#include "IRFC.h"
#include "RFC.h"

#include <fstream>
void				recvCmd(RFC::RecvCommand cmd, Network::Socket &socket) {
	static int i = 0;
	std::fstream tata("tata.txt", std::fstream::in | std::fstream::app);
	int nb;
	IRFC::Dir		dir;
	IRFC::Coord		coord;

	switch (cmd)
	{
	case RFC::RECVHANDSHAKE:
		break;
	case RFC::RECVMOVE:
		char buff[8];
		RFC::Move mov;


		nb = socket.in().get(buff, 8);
		mov.coord.posX = *(short int*)(buff);
		mov.coord.posY = *(short int*)(buff + 2);
		mov.dir.dirX = *(short int*)(buff + 4);
		mov.dir.dirY = *(short int*)(buff + 6);
		//_onMoveEvent(*this, )
		//tata << i++ << "------------------------------------------" << std::endl;
		//tata << cmd << " x =" << coord.posX << "\ny =" << coord.posY << "\ndirX =" << dir.dirX << "\ndirY =" << dir.dirY << std::endl;
	case RFC::RECVSHOOT:
		break;
	case RFC::RECVCOLLISION:
		break;
	case RFC::RECVHITMONSTER:
		break;
	case RFC::RECVKILLMONSTER:
		break;
	default:
		break;
	}
	tata.close();
}

void	onReceiveEvent2(Network::Socket &socket)
{
	::hpl::Logger::out("Receive");
	char buff[1];
	int nb = socket.in().get(buff, 1);
	RFC::RecvCommand cmd = (RFC::RecvCommand)*(char *)(buff);
	recvCmd(cmd, socket);
}

void	onEndEvent2(Network::Socket const &socket)
{
	::hpl::Logger::out("End");
}

void	onConnectEvent(Network::Server &server, Network::Socket &socket)
{
	::hpl::Logger::out("New client");
	socket.onRecive(::hpl::bind(&onReceiveEvent2, ::hpl::Placeholder::_1));
	socket.onEnd(::hpl::bind(&onEndEvent2, ::hpl::Placeholder::_1));
}
void	onDisconnectEvent(Network::Server &server, Network::Socket const &socket)
{
	::hpl::Logger::out("Losing client");
}
void	onEndEvent(Network::Server const &server)
{
	::hpl::Logger::out("Stopping server");
}

void	onListenEvent(Network::Server &server)
{
	::hpl::Logger::out("Listen on 2222");
	server.onDisconnect(::hpl::bind(&onDisconnectEvent, ::hpl::Placeholder::_1, ::hpl::Placeholder::_2));
	server.onEnd(::hpl::bind(&onEndEvent, ::hpl::Placeholder::_1));
}

void	onServerStart(Network::Server &server)
{
	::hpl::Logger::out("Starting server");
	server.onConnect(::hpl::bind(&onConnectEvent, ::hpl::Placeholder::_1, ::hpl::Placeholder::_2));
	server.listen<Network::tcp::ip4>(2222, ::hpl::bind(&onListenEvent, ::hpl::Placeholder::_1));
}

int		main(int argc, char *argv[], char *env[])
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "R-Type");
	Game			game;
	sf::Clock		clock;
	Network::Server	*server = Network::Server::create(::hpl::bind(&onServerStart, ::hpl::Placeholder::_1));

	std::srand(static_cast<unsigned int>(std::time(NULL)));
	try {
		game.init();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	while (window.isOpen())
	{
		sf::Time time = clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		game.run();
		TransformSystem::update(game.getWorld(), time);
		window.clear();
		RenderSystem::update(&window, game.getWorld());
		window.display();
	}
	delete server;
	return(0);
}