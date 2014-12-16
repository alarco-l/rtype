#pragma once

#include "World.h"

class				ISystem
{
public:
	virtual			~ISystem() {}
	virtual void	update(World &world, const sf::Time &elapsed) const = 0;
};