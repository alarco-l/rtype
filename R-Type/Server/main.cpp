#include <SFML/Graphics.hpp>

#include <iostream>

#include "BasicTypes.h"
#include "World.h"
#include "Systems.h"
#include "ComponentFactory.h"
#include "ResourceManager.h"

sf::Vector2f normalize(const sf::Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "R-Type");
	World	world;
	ResourceManager resource;
	sf::Clock clock;
	sf::Texture texture;
	sf::Sprite sprite;
	float R = 100.f;
	float d = 50.f;
	float x, y, tmp = 0.f;
	uint id;

	resource.loadTexture("../R-Type/textures/hero.png");
	id = world.createEmptyEntity();
	world.addRenderComponent(id, ComponentFactory::createRenderComponent(resource.getTexture("../R-Type/textures/hero.png")));
	world.addTransformComponent(id, ComponentFactory::createTransformComponent(sf::Vector2f(1021, 728), sf::Vector2f(0, 0), sf::Vector2f(0.05f, 0.20f)));
	world.addMovementComponent(id, ComponentFactory::createMovementComponent(200, sf::Vector2f(0, 0)));
	while (window.isOpen())
	{
		sf::Time time = clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		tmp += 0.001f;
		x = (R * tmp) - (d * sin((tmp)));
		y = (R - d * cos(tmp));
//		world.transformComponents[id]->position = sf::Vector2f(x, y);
//		sf::Vector2f direction;
//		direction = normalize(sf::Vector2f(x, y) - world.transformComponents[id]->position);
//		std::cout << direction.x << " - " << direction.y << std::endl;
//		std::cout << world.transformComponents[id]->position.x << "|    -     |" << world.transformComponents[id]->position.y << std::endl;
		world.movementComponents[id]->direction = sf::Vector2f(x - world.transformComponents[id]->position.x, y - world.transformComponents[id]->position.y);
		TransformSystem::update(world, time);
		window.clear();
		RenderSystem::update(&window, world);
		window.display();
	}
	return(0);
}