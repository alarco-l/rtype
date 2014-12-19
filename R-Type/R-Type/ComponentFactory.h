#pragma once

#include "Components.h"

class							ComponentFactory
{
public:
	static RenderComponent		*createRenderComponent(const sf::Texture * const tex);

	static TransformComponent	*createTransformComponent(const sf::Vector2f &pos,
														  const sf::Vector2f &sca = sf::Vector2f(1.0f, 1.0f),
														  const float rot = 0.0f);

	static AnimationComponent	*createAnimationComponent(const std::vector<const sf::Texture * const> &anims,
														  const sf::Time &maxLifetime);

	static MovementComponent	*createMovementComponent(const float vel,
														 const sf::Vector2f &dir);

	static EmitterComponent		*createEmitterComponent(const sf::Vector2f &lifetimeInterval,
														const bool respawn,
														const sf::Vector2f &propagationInterval = sf::Vector2f(0.0f, 360.0f),
														const sf::Vector2f &velocityInterval = sf::Vector2f(30.0f, 100.0f),
														const sf::Vector2f &scaleInterval = sf::Vector2f(1.0f, 1.0f));

	static ParticleComponent	*createParticleComponent(const sf::Time &lifetime);
private:
	ComponentFactory();
};