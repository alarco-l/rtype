#pragma once

#include "ISystem.h"

class								ParticleSystem : public ISystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	void							update(World &world, const sf::Time &elapsed) const;
private:
	ParticleSystem(const ParticleSystem &rhs);
	ParticleSystem &operator=(const ParticleSystem &rhs);

	void							resetParticle(World &world, const unsigned int id) const;
};