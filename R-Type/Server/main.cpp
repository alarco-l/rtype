#include <SFML/Graphics.hpp>

#include "World.h"
#include "Systems.h"
#include "ComponentFactory.h"
#include "ResourceManager.h"
#include "Game.h"

#include "RFC.h"

#include <fstream>
#include "RFCManager.h"

int		main(int argc, char *argv[], char *env[])
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "R-Type");
	Game			game;
	sf::Clock		clock;
	RFCManager		*rfcManager = new RFCManager();
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
	return(0);
}