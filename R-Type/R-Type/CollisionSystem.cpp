#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{
}

CollisionSystem::~CollisionSystem()
{
}

void							CollisionSystem::update(World &world) const
{
	for (unsigned int i = 0; i != world.entityCount; ++i)
	{
		CollisionComponent		*col;
		TransformComponent		*xform;

		col = world.collisionComponents[i];
		xform = world.transformComponents[i];

		for (unsigned int j = 0; j != col->aabb.size(); ++j)
		{
			sf::FloatRect		aabb;

			aabb = xform->transform.transformRect(col->aabb[j]);

		}
	}
}