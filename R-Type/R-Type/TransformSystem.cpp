#include "TransformSystem.h"

TransformSystem::TransformSystem()
{
}

TransformSystem::~TransformSystem()
{
}

void						TransformSystem::update(World &world, const sf::Time &elapsed) const
{
	for (unsigned int i = 0; i != world.entityCount; ++i)
	{
		TransformComponent	*xform = world.transformComponents[i];
		MovementComponent	*mov = world.movementComponents[i];

		if (xform)
		{
			if (mov)
				this->updatePosition(xform, mov, elapsed);
			// TODO : rotation / scale
			// compute transform a chaque fois ? ou just quand ça a change
			this->computeTransform(xform);
		}
	}
}

void						TransformSystem::updatePosition(TransformComponent *xform, MovementComponent *mov, const sf::Time &elapsed) const
{
	sf::Vector2f			direction;
	float					length;

	direction = mov->direction;
	length = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0.0f)
		direction /= length;
	xform->position += direction * mov->velocity * elapsed.asSeconds();
}

void						TransformSystem::computeTransform(TransformComponent *xform) const
{
	float angle = -xform->rotation * 3.141592654f / 180.f;
	float cosine = std::cosf(angle);
	float sine = std::sinf(angle);
	float sxc = xform->scale.x * cosine;
	float syc = xform->scale.y * cosine;
	float sxs = xform->scale.x * sine;
	float sys = xform->scale.y * sine;
	float tx = -xform->origin.x * sxc - xform->origin.y * sys + xform->position.x;
	float ty = xform->origin.x * sxs - xform->origin.y * syc + xform->position.y;

	xform->transform = sf::Transform(sxc, sys, tx, -sxs, syc, ty, 0.0f, 0.0f, 1.0f);
}