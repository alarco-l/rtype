#pragma once

#include <vector>

#include "Components.h"

class									World
{
public:
	World();
	~World();

	/* Methodes temporaires pour creer des entites (en attendant une factory ?) */
	void								createStaticEntity(const sf::Texture * const,
														   const sf::Vector2f &position,
														   const sf::Vector2f &scale = sf::Vector2f(1.0f, 1.0f));
	void								createEntity(const sf::Texture * const texture,
											   		 const sf::Vector2f &position,
													 const sf::Vector2f &scale = sf::Vector2f(1.0f, 1.0f),
													 const float velocity = 50.0f);
	void								createAnimatedEntity(const std::vector<const sf::Texture * const> &textures,
															 const sf::Time &duration,
															 const sf::Vector2f &position,
															 const sf::Vector2f &scale = sf::Vector2f(1.0f, 1.0f),
															 const float velocity = 50.0f);
	void								createParticleEffect(const unsigned int maxParticleCount,
															 const bool respawn,
															 const sf::Texture * const texture,
															 const sf::Vector2f &position = sf::Vector2f(0.0f, 0.0f));
															 

	unsigned int						entityCount;
	std::vector<RenderComponent *>		renderComponents;
	std::vector<TransformComponent *>	transformComponents;
	std::vector<MovementComponent *>	movementComponents;
	std::vector<ParticleComponent *>	particleComponents;
	std::vector<EmitterComponent *>		emitterComponents;
	std::vector<AnimationComponent *>	animationComponents;
	std::vector<CollisionComponent *>	collisionComponents;
};