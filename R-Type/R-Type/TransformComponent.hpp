#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transform.hpp>

struct													TransformComponent
{
	TransformComponent(const sf::Vector2f &pos,
					   const sf::Vector2f &sca = sf::Vector2f(1.0f, 1.0f),
					   const float rot = 0.0f) :
		position(pos), scale(sca), rotation(rot), origin(sf::Vector2f(0.0f, 0.0f))
	{
	}

	sf::Vector2f										position;
	sf::Vector2f										scale;
	float												rotation;
	sf::Vector2f										origin;
	sf::Transform										transform;
};