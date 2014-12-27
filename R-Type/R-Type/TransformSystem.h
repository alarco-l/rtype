#pragma once

#include "World.h"
#include "RFCClient.h"

class							TransformSystem
{
public:
	static void					update(World &world, const sf::Time &elapsed, RFCClient *rfc);
	TransformSystem();
	TransformSystem(const TransformSystem &rhs);
	TransformSystem &operator=(const TransformSystem &rhs);

	static void					applyScroll(TransformComponent *xform, ScrollComponent *scroll, const sf::Time &elapsed);
	static void					applyMovement(TransformComponent *xform, MovementComponent *mov, const sf::Time &elapsed);
	static void					applySpin(TransformComponent *xform, SpinComponent *spin, const sf::Time &elapsed);
	static void					computeTransform(TransformComponent *xform);
};