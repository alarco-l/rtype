#pragma once

#include <vector>
#include <SFML/Graphics/Rect.hpp>

struct												CollisionComponent
{
	sf::FloatRect									bounds;
	std::vector<sf::FloatRect>						aabb;
	// Coordonnées dans la collision grid
};