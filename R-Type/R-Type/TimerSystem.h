#pragma once

#include "World.h"

class								TimerSystem
{
public:
	static void						update(World &world, const sf::Time &elapsed);
private:
	TimerSystem();
	TimerSystem(const TimerSystem &rhs);
	TimerSystem &operator=(const TimerSystem &rhs);
};