#include "ParticleSystem.h"

void							ParticleSystem::update(World &world, const sf::Time &elapsed)
{
	for (unsigned int i = 0; i != world.entityCount; ++i)
	{
		ParticleComponent		*particle = world.particleComponents[i];
		RenderComponent			*render = world.renderComponents[i];

		if (particle)
		{
			particle->lifetime -= elapsed;
			if (particle->lifetime <= sf::Time::Zero)
				resetParticle(world, i);
			//TODO : respawn = false -> delete emitter and particles

			if (render)
			{
				float			ratio = particle->lifetime.asSeconds() / particle->maxLifetime.asSeconds();

				render->vertices[0].color.a = static_cast<sf::Uint8>(ratio * 255);
				render->vertices[1].color.a = static_cast<sf::Uint8>(ratio * 255);
				render->vertices[2].color.a = static_cast<sf::Uint8>(ratio * 255);
				render->vertices[3].color.a = static_cast<sf::Uint8>(ratio * 255);
			}
		}
	}
}

// Enlever les if de "au cas ou" ?

void							ParticleSystem::resetParticle(World &world, const unsigned int id)
{
	ParticleComponent			*particle = world.particleComponents[id];
	TransformComponent			*xform = world.transformComponents[id];
	MovementComponent			*mov = world.movementComponents[id];
	EmitterComponent			*emitter = world.emitterComponents[particle->emitterId];

	if (emitter)
	{
		sf::Vector2f			emitterPos = world.transformComponents[particle->emitterId]->position;
		sf::Vector2f			velocityInterval = emitter->velocityInterval;
		sf::Vector2f			propagationInterval = emitter->propagationInterval;
		sf::Vector2f			lifetimeInterval = emitter->lifetimeInterval;
		sf::Vector2f			scaleInterval = emitter->scaleInterval;
		float					angle;

		particle->maxLifetime = sf::seconds(std::fmodf(static_cast<float>(std::rand()), lifetimeInterval.y - lifetimeInterval.x + 0.000001f) + lifetimeInterval.x);
		particle->lifetime = particle->maxLifetime;
		if (mov)
		{
			mov->velocity = std::fmodf(static_cast<float>(std::rand()), velocityInterval.y - velocityInterval.x + 0.000001f) + velocityInterval.x;
			angle = std::fmodf(static_cast<float>(std::rand()), propagationInterval.y - propagationInterval.x + 0.000001f) + propagationInterval.x;
			angle *= 3.141592f / 180.0f;
			mov->direction = sf::Vector2f(std::cosf(angle) * mov->velocity, std::sinf(angle) * mov->velocity);
		}
		if (xform)
		{
			float				scale;

			scale = std::fmodf(static_cast<float>(std::rand()), scaleInterval.y - scaleInterval.x + 0.000001f) + scaleInterval.x;
			xform->scale.x *= scale;
			xform->scale.y *= scale;
			xform->position = emitterPos;
		}
	}
	// TODO : rotation
}