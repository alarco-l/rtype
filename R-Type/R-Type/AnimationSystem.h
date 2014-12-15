#pragma once

#include "World.h"

class						AnimationSystem
{
public:
	AnimationSystem();
	~AnimationSystem();
	void					update(World &world, const sf::Time &elapsed) const;
private:
	AnimationSystem(const AnimationSystem &rhs);
	AnimationSystem &operator=(const AnimationSystem &rhs);
};