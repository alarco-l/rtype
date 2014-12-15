#include <SFML/Graphics.hpp>
#include <iostream>

#include "ResourceManager.h"
#include "World.h"
#include "Systems.h"

int								main()
{
	sf::RenderWindow			window(sf::VideoMode(1600, 900), "R-Type");
	sf::Event					event;
	ResourceManager				resourceManager;
	RenderSystem				renderSystem;
	TransformSystem				transformSystem;
	ParticleSystem				particleSystem;
	AnimationSystem				animationSystem;
	World						world;
	sf::Clock					clock;
	sf::Time					elapsed;
	std::vector<const sf::Texture * const> textures;

	std::srand(static_cast<unsigned int>(std::time(NULL)));

	resourceManager.loadTexture("textures/hero.png");
	resourceManager.loadTexture("textures/fireball.png");
	resourceManager.loadTexture("textures/explosion0.png");
	resourceManager.loadTexture("textures/explosion1.png");
	resourceManager.loadTexture("textures/explosion2.png");
	resourceManager.loadTexture("textures/explosion3.png");
	resourceManager.loadTexture("textures/explosion4.png");
	resourceManager.loadTexture("textures/explosion5.png");

	textures.push_back(resourceManager.getTexture("textures/explosion0.png"));
	textures.push_back(resourceManager.getTexture("textures/explosion1.png"));
	textures.push_back(resourceManager.getTexture("textures/explosion2.png"));
	textures.push_back(resourceManager.getTexture("textures/explosion3.png"));
	textures.push_back(resourceManager.getTexture("textures/explosion4.png"));
	textures.push_back(resourceManager.getTexture("textures/explosion5.png"));

	world.createEntity(resourceManager.getTexture("textures/hero.png"), sf::Vector2f(0.0f, 0.0f));
	world.createParticleEffect(20, true, resourceManager.getTexture("textures/fireball.png"), sf::Vector2f(800.0f, 450.0f));
	world.createAnimatedEntity(textures, sf::seconds(0.10f), sf::Vector2f(0.0f, 450.0f));

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		elapsed = clock.restart();

		window.clear();

		particleSystem.update(world, elapsed);
		transformSystem.update(world, elapsed);
		animationSystem.update(world, elapsed);
		renderSystem.update(window, world);

		window.display();
	}
	return (EXIT_SUCCESS);
}

