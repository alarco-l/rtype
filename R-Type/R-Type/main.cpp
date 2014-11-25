#include <SFML/Graphics.hpp>
#include <iostream>

#include "ResourceManager.h"
#include "PositionComponent.hpp"
#include "MovementComponent.hpp"
#include "RenderComponent.hpp"

int								main()
{
	sf::RenderWindow			window(sf::VideoMode(800, 600), "R-Type");
	sf::Event					event;
	ResourceManager				resourceManager;

	resourceManager.loadTexture("textures/hero.png");

	RenderComponent				render(resourceManager.getTexture("textures/hero.png"), sf::Vector2f(0.25f, 0.25f));

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(render.vertices, render.texture);
		window.display();
	}
	resourceManager.unloadTexture("textures/hero.png");
	return (EXIT_SUCCESS);
}

