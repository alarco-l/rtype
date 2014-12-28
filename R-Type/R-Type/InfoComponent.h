#pragma once

#include <SFML/System/Time.hpp>
#include <vector>

struct										InfoComponent
{
	unsigned int							life;
	unsigned int							shield;
	unsigned int							score;
	unsigned int							team;
	unsigned int							damageReceived;
	std::vector<const sf::Texture * const>	deathAnimation;
	sf::Time								maxLifetime;
	bool									dead;
};