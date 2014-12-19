#include <SFML/Graphics.hpp>
#include <iostream>

#include "ResourceManager.h"
#include "World.h"
#include "Systems.h"
#include "Game.h"

int								main()
{
	Game						game;

	std::srand(static_cast<unsigned int>(std::time(NULL)));

	/*resourceManager.loadTexture("textures/hero.png");
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
	textures.push_back(resourceManager.getTexture("textures/explosion5.png"));*/

	/*world.createMovingEntity(resourceManager.getTexture("textures/hero.png"), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.5f, 0.5f));
	world.createParticleEffect(20, true, resourceManager.getTexture("textures/fireball.png"), sf::Vector2f(800.0f, 450.0f));
	world.createAnimatedEntity(textures, sf::seconds(0.10f), sf::Vector2f(0.0f, 450.0f));*/

	if (!game.initialize(sf::Vector2u(1920, 1080), "R-Type"))
		return (EXIT_FAILURE);
	game.run();
	game.exit();

	return (EXIT_SUCCESS);
}