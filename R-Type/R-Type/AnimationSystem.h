#pragma once

#include "World.h"

class						AnimationSystem
{
public:
	static void				update(World &world, const sf::Time &elapsed);
private:
	AnimationSystem();
	AnimationSystem(const AnimationSystem &rhs);
	AnimationSystem &operator=(const AnimationSystem &rhs);
};