#pragma once

#include "World.h"

class								ParticleSystem
{
public:
	static void						update(World &world, const sf::Time &elapsed);
private:
	ParticleSystem();
	ParticleSystem(const ParticleSystem &rhs);
	ParticleSystem &operator=(const ParticleSystem &rhs);

	static void						resetParticle(World &world, const unsigned int id);
};