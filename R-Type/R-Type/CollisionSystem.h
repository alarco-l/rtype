#pragma once

#include "World.h"
#include "../hpl/Network/Client.h"

#include <set>

class																CollisionSystem
{
public:
	static void														update(World &world, const sf::Vector2u &precision, const sf::Vector2u &size, const Network::Client *client);
private:
	typedef std::vector<std::vector<std::set<unsigned int> > >		collisionGrid;

	CollisionSystem();
	CollisionSystem(const CollisionSystem &rhs);
	CollisionSystem &operator=(const CollisionSystem &rhs);

	static std::vector<sf::Vector2f>								getEntityBounds(const sf::Transform &transform, const sf::Vector2f &size);
	static void														projectAxis(const std::vector<sf::Vector2f> &points, const sf::Vector2f &axis, float &min, float &max);
	static std::vector<sf::Vector2u>								addEntityToGrid(collisionGrid &grid, const sf::Vector2u &cellSize, const sf::FloatRect &aabb, const unsigned int id);
	static bool														collide(const std::vector<sf::Vector2f> &self, const std::vector<sf::Vector2f> &target);
};