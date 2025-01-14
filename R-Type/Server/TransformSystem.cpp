#include "TransformSystem.h"

void						TransformSystem::update(World &world, const sf::Time &elapsed)
{
	for (unsigned int i = 0; i != world.entityCount; ++i)
	{
		TransformComponent	*xform = world.transformComponents[i];
		ScrollComponent		*scroll = world.scrollComponent[i];
		MovementComponent	*mov = world.movementComponents[i];
		SpinComponent		*spin = world.spinComponents[i];

		if (xform)
		{
			if (scroll)
				applyScroll(xform, scroll, elapsed);
			if (mov)
				applyMovement(xform, mov, elapsed);
			if (spin)
				applySpin(xform, spin, elapsed);
			computeTransform(xform);
		}
	}
}

void							TransformSystem::applyScroll(TransformComponent *xform, ScrollComponent *scroll, const sf::Time &elapsed)
{
	xform->position += scroll->direction * scroll->speed * elapsed.asSeconds();
}

void						TransformSystem::applyMovement(TransformComponent *xform, MovementComponent *mov, const sf::Time &elapsed)
{
	sf::Vector2f			direction;
	//float					length;

	direction = mov->direction;
	//length = sqrt(direction.x * direction.x + direction.y * direction.y);
	//if (length != 0.0f)
	//	direction /= length;
	xform->position += direction * mov->velocity * elapsed.asSeconds();
}

void						TransformSystem::applySpin(TransformComponent *xform, SpinComponent *spin, const sf::Time &elapsed)
{
	xform->rotation += spin->direction * spin->speed * elapsed.asSeconds();
}

void						TransformSystem::computeTransform(TransformComponent *xform)
{
	xform->transform = sf::Transform::Identity;
	xform->transform.translate(xform->position);
	xform->transform.rotate(xform->rotation, sf::Vector2f(xform->size.x / 2, xform->size.y / 2));
	xform->transform.scale(xform->scale);
}