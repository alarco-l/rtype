#pragma once

#include <SFML/System/Time.hpp>

struct										ParticleComponent
{
	ParticleComponent(const sf::Time &_lifetime) :
		lifetime(_lifetime), maxLifetime(_lifetime)
	{
	}

	sf::Time								lifetime;
	sf::Time								maxLifetime;
	unsigned int							emitterId;
};