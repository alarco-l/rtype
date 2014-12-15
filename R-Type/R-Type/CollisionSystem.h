#pragma once

#include "ISystem.h"

class							CollisionSystem : public ISystem
{
public:
	CollisionSystem();
	~CollisionSystem();
	void						update(World &world) const;
private:
	CollisionSystem(const CollisionSystem &rhs);
	CollisionSystem &operator=(const CollisionSystem &rhs);
};