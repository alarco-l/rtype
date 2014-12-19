#include "CollisionSystem.h"

CollisionSystem::CollisionSystem(const sf::Vector2u &precision, const sf::Vector2u &displaySize) 
{
	_collisionGrid.resize(precision.x);
	for (unsigned int i = 0; i != precision.x; ++i)
		_collisionGrid[i].resize(precision.y);
//	_cellSize = sf::Vector2f(displaySize.x / precision.x, displaySize.y / precision.y);
}

CollisionSystem::~CollisionSystem()
{
}

void							CollisionSystem::update(World &world) const
{
	/*for (unsigned int i = 0; i != world.entityCount; ++i)
	{
		CollisionComponent		*col;
		TransformComponent		*xform;

		col = world.collisionComponents[i];
		xform = world.transformComponents[i];

		if (col && xform)
		{*/
			// add entities one by one to the collision grid
		//}
		
		


		/* get entity collisionGrid cell id
		   for (grid[cell id].size())
		   {
				other = grid[cell id][i];
				for (col->aabb.size())
				{
					for (other->aabb.size())
					{
						if (collide)
							...
					}
				}
		   }
		
		*/


		/*for (unsigned int j = 0; j != col->aabb.size(); ++j)
		{
			sf::FloatRect		aabb;

			aabb = xform->transform.transformRect(col->aabb[j]);

		}*/
	//}
}