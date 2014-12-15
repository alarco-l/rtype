#pragma once

#include <SFML/System/Vector2.hpp>

struct									MovementComponent
{
	MovementComponent(const float vel,
					  const sf::Vector2f &dir) :
		velocity(vel), direction(dir)
	{
	}

	float								velocity;
	sf::Vector2f						direction;
};