#pragma once

#include "World.h"

class							TransformSystem
{
public:
	TransformSystem();
	~TransformSystem();
	void						update(World &world, const sf::Time &elapsed) const;
private:
	TransformSystem(const TransformSystem &rhs);
	TransformSystem &operator=(const TransformSystem &rhs);

	void						updatePosition(TransformComponent *xform, MovementComponent *mov, const sf::Time &elapsed) const;
	void						computeTransform(TransformComponent *xform) const;
};