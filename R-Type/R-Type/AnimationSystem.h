#pragma once

#include "ISystem.h"

class						AnimationSystem : public ISystem
{
public:
	AnimationSystem();
	~AnimationSystem();
	void					update(World &world, const sf::Time &elapsed) const;
private:
	AnimationSystem(const AnimationSystem &rhs);
	AnimationSystem &operator=(const AnimationSystem &rhs);
};