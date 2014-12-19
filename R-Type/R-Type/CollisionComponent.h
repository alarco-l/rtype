#pragma once

#include <vector>
#include <SFML/Graphics/Rect.hpp>

struct												CollisionComponent
{
	CollisionComponent(const std::vector<sf::FloatRect> &_aabb) :
		aabb(_aabb)
	{
	}

	std::vector<sf::FloatRect>						aabb;
	// Coordonnées dans la collision grid
};