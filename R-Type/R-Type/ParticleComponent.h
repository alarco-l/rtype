#pragma once

#include <SFML/System/Time.hpp>

struct										ParticleComponent
{
	sf::Time								lifetime;
	sf::Time								maxLifetime;
	unsigned int							emitterId;
};