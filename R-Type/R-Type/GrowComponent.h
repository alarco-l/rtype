#pragma once

#include <SFML/System/Vector2.hpp>

struct					GrowComponent
{
	sf::Vector2f		direction;
	float				speed;
	sf::Vector2f		limit;
};