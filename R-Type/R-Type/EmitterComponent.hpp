#pragma once

#include <vector>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

struct									EmitterComponent
{
	EmitterComponent(const sf::Vector2f &_lifetimeInterval,
					 const bool _respawn,
					 const sf::Vector2f &_propagationInterval = sf::Vector2f(0.0f, 360.0f),
					 const sf::Vector2f &_velocityInterval = sf::Vector2f(30.0f, 100.0f),
					 const sf::Vector2f	&_scaleInterval = sf::Vector2f(1.0f, 1.0f)) :
		respawn(_respawn), lifetimeInterval(_lifetimeInterval), propagationInterval(_propagationInterval), velocityInterval(_velocityInterval), scaleInterval(_scaleInterval)
	{
	}

	bool								respawn;
	sf::Vector2f						lifetimeInterval;
	sf::Vector2f						propagationInterval;
	sf::Vector2f						velocityInterval;
	sf::Vector2f						scaleInterval;
	std::vector<unsigned int>			particleId;
	/*
		(- intervalle de rotation ?)
	*/
};