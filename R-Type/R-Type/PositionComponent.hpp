#pragma once

#include <SFML/System/Vector2.hpp>

struct									PositionComponent
{
	PositionComponent(const sf::Vector2f &_position = sf::Vector2f(0.0f , 0.0f)) : position(_position)
	{
	}

	sf::Vector2f						position;
};