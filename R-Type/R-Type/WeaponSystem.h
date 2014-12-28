#pragma once

#include "World.h"
#include "GameSpecificFactory.h"

class									WeaponSystem
{
public:
	static void							update(World &world, const sf::Time &elapsed, GameSpecificFactory &factory, const sf::Vector2u &screenSize);
private:
	WeaponSystem();
	WeaponSystem(const WeaponSystem &rhs);
	WeaponSystem &operator=(const WeaponSystem &rhs);
};