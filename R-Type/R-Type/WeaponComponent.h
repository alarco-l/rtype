#pragma once

#include <SFML/System/Time.hpp>

struct								WeaponComponent
{
	sf::Time						maxCooldown;
	sf::Time						cooldown;
	bool							fire;
	unsigned int					owner;
	unsigned int					projectileType;
};