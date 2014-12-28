#include <SFML/Graphics.hpp>

#include <iostream>

#include "BasicTypes.h"
#include "World.h"
#include "Systems.h"
#include "ComponentFactory.h"
#include "ResourceManager.h"

#include "hpl.h"
#include "Network/Server.h"

sf::Vector2f normalize(const sf::Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f((source.x / length), (source.y / length));
	else
		return sf::Vector2f(source.x, source.y);
}

void	onReceiveEvent2(Network::Socket &socket)
{
	::hpl::Logger::out("Receive");
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
	server.listen<Network::udp::ip4>(2222, ::hpl::bind(&onListenEvent, ::hpl::Placeholder::_1));
}

int		main(int argc, char *argv[], char *env[])
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "R-Type");
	World	world;
	ResourceManager resource;
	sf::Clock clock;
	sf::Texture texture;
	sf::Sprite sprite;
	float d = 50.f;
	float R = 100.f;
	float x, y, tmp = 0.f;
	y = window.getSize().y / 2;
	uint id;

	resource.loadTexture("../R-Type/textures/hero.png");
	id = world.createEmptyEntity();
	world.addRenderComponent(id, ComponentFactory::createRenderComponent(resource.getTexture("../R-Type/textures/hero.png")));
	world.addTransformComponent(id, ComponentFactory::createTransformComponent(sf::Vector2f(1021, 728), sf::Vector2f(0, y), sf::Vector2f(0.05f, 0.20f)));
	world.addMovementComponent(id, ComponentFactory::createMovementComponent(50, sf::Vector2f(0, y)));
	Network::Server	*server = Network::Server::create(::hpl::bind(&onServerStart, ::hpl::Placeholder::_1));
	while (window.isOpen())
	{
		sf::Time time = clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		tmp += 0.002f;
		x = (R * tmp) - (d * sin((tmp)));
		y = (R - d * cos(tmp));
		sf::Vector2f direction;
		direction = sf::Vector2f(x, y) - world.transformComponents[id]->position;
		world.movementComponents[id]->direction = sf::Vector2f(direction.x, direction.y);
		TransformSystem::update(world, time);
		window.clear();
		RenderSystem::update(&window, world);
		window.display();
	}
	delete server;
	return(0);
}