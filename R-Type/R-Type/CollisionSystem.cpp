#include "CollisionSystem.h"
#include <algorithm>

void									CollisionSystem::update(World &world, const sf::Vector2u &precision, const sf::Vector2u &size)
{
	collisionGrid						grid;
	sf::Vector2u						cellSize = sf::Vector2u(size.x / precision.x, size.y / precision.y);

	grid.resize(precision.x);
	for (unsigned int i = 0; i != precision.x; ++i)
		grid[i].resize(precision.y);

	for (unsigned int i = 0; i < world.entityCount; ++i)
	{
		CollisionComponent				*col;
		TransformComponent				*xform;

		col = world.collisionComponents[i];
		xform = world.transformComponents[i];

		if (col && xform)
		{
			std::vector<sf::Vector2f>	bounds = getEntityBounds(xform->transform, xform->size); // bounds of entity in global space after transforms
			sf::FloatRect				aabb = xform->transform.transformRect(sf::FloatRect(sf::Vector2f(0.0f, 0.0f), xform->size)); // axis aligned bounding box for entity
			std::vector<sf::Vector2u>	cells; // cells in which the entity is contained

			cells = addEntityToGrid(grid, cellSize, aabb, i); // add entities one by one to the collision grid

			//collision inside the cells in which the entity is contained
			for (std::vector<sf::Vector2u>::iterator it = cells.begin(); it != cells.end(); ++it)
			{
				for (std::set<unsigned int>::iterator it2 = grid[it->x][it->y].begin(); it2 != grid[it->x][it->y].end(); ++it2)
				{
					if (*it2 != i) // don't test entity against itself
					{
						std::vector<sf::Vector2f> target = getEntityBounds(world.transformComponents[*it2]->transform, world.transformComponents[*it2]->size);

						if (collide(bounds, target))
						{
							// collision happens here
							resolveCollision(i, *it2, world);
						}
					}
				}
			}
		}

	}
}

void									CollisionSystem::resolveCollision(const unsigned int self, const unsigned int target, World &world)
{
	ProjectileComponent					*selfProj = world.projectileComponents[self];
	InfoComponent						*selfInfo = world.infoComponents[self];
	InfoComponent						*targetInfo = world.infoComponents[target];
	ProjectileComponent					*targetProj = world.projectileComponents[target];

	if (selfProj) // self is projectile
	{
		if (targetInfo && selfInfo && selfInfo->team != targetInfo->team)
		{
			targetInfo->damageReceived = selfProj->damage;
			world.infoComponents[selfProj->owner]->score += 10;
			if (!selfProj->persistent)
				selfInfo->dead = true;
		}
		else if (selfInfo && !targetInfo && !selfProj->persistent)
			selfInfo->dead = true;
		else if (!selfInfo && !targetInfo && !selfProj->persistent)
			world.destroyEntity(self);

	}
	else if (targetProj) // target is projectile
	{
		if (targetInfo && selfInfo && selfInfo->team != targetInfo->team)
		{
			selfInfo->damageReceived = targetProj->damage;
			world.infoComponents[targetProj->owner]->score += 10;
			if (!targetProj->persistent)
				targetInfo->dead = true;
		}
		else if (targetInfo && !selfInfo && !targetProj->persistent)
			targetInfo->dead = true;
		else if (!targetInfo && selfInfo && !targetProj->persistent)
			world.destroyEntity(target);
	}
}

std::vector<sf::Vector2u>				CollisionSystem::addEntityToGrid(collisionGrid &grid, const sf::Vector2u &cellSize, const sf::FloatRect &aabb, const unsigned int id)
{
	std::vector<sf::Vector2u>			cells;

	for (unsigned int i = 0; i != grid.size(); ++i)
	{
		for (unsigned int j = 0; j != grid[i].size(); ++j)
		{
			sf::FloatRect				cell = sf::FloatRect(sf::Vector2f(static_cast<float>(i * cellSize.x), static_cast<float>(j * cellSize.y)), sf::Vector2f(cellSize));

			if (aabb.intersects(cell))
			{
				grid[i][j].insert(id);
				if (std::find(cells.begin(), cells.end(), sf::Vector2u(i, j)) == cells.end())
					cells.push_back(sf::Vector2u(i, j));
			}
		}
	}

	return (cells);
}

std::vector<sf::Vector2f>				CollisionSystem::getEntityBounds(const sf::Transform &transform, const sf::Vector2f &size)
{
	std::vector<sf::Vector2f>			points;

	points.push_back(transform.transformPoint(0.f, 0.f));
	points.push_back(transform.transformPoint(size.x, 0.f));
	points.push_back(transform.transformPoint(size.x, size.y));
	points.push_back(transform.transformPoint(0.f, size.y));

	return (points);
}

void									CollisionSystem::projectAxis(const std::vector<sf::Vector2f> &points, const sf::Vector2f &axis, float &min, float &max)
{
	min = (points[0].x * axis.x + points[0].y * axis.y);
	max = min;

	for (int j = 1; j < 4; j++)
	{
		float Projection = (points[j].x * axis.x + points[j].y * axis.y);

		if (Projection < min)
			min = Projection;
		if (Projection > max)
			max = Projection;
	}
}

bool									CollisionSystem::collide(const std::vector<sf::Vector2f> &self, const std::vector<sf::Vector2f> &target)
{
	sf::Vector2f						axes[4];

	axes[0] = sf::Vector2f(self[1].x - self[0].x, self[1].y - self[0].y);
	axes[1] = sf::Vector2f(self[1].x - self[2].x, self[1].y - self[2].y);
	axes[2] = sf::Vector2f(target[0].x - target[3].x, target[0].y - target[3].y);
	axes[3] = sf::Vector2f(target[0].x - target[1].x, target[0].y - target[1].y);

	for (unsigned int i = 0; i < 4; ++i)
	{
		float minSelf;
		float maxSelf;
		float minTarget;
		float maxTarget;

		projectAxis(self, axes[i], minSelf, maxSelf);
		projectAxis(target, axes[i], minTarget, maxTarget);

		if (!((minTarget <= maxSelf) && (maxTarget >= minSelf)))
			return false;
	}
	return (true);
}