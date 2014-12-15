#pragma once

#include "World.h"

class							CollisionSystem
{
public:
	CollisionSystem();
	~CollisionSystem();
	void						update(World &world) const;
private:
	CollisionSystem(const CollisionSystem &rhs);
	CollisionSystem &operator=(const CollisionSystem &rhs);
};