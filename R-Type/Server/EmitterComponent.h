#pragma once

#include <vector>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

struct									EmitterComponent
{
	bool								respawn;
	sf::Vector2f						lifetimeInterval;
	sf::Vector2f						propagationInterval;
	sf::Vector2f						velocityInterval;
	sf::Vector2f						scaleInterval;
	// intervalle de rotation ?
	std::vector<unsigned int>			particleId;
	
};