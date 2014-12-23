#pragma once

#include <SFML/System/Vector2.hpp>

struct									MovementComponent
{
	float								velocity;
	sf::Vector2f						direction;
};