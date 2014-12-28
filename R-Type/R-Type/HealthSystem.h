#pragma once 

#include "World.h"
#include "GameSpecificFactory.h"

class									HealthSystem
{
public:
	static void							update(World &world, const sf::Time &elapsed, GameSpecificFactory &factory);
private:
	HealthSystem();
};