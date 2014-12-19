#pragma once

#include <vector>

#include "ComponentFactory.h"

class									World
{
public:
	World();
	~World();

	const unsigned int					createStaticEntity(const sf::Texture * const texture,
													 	   const sf::Vector2f &position,
														   const sf::Vector2f &scale = sf::Vector2f(1.0f, 1.0f));
	const unsigned int					createMovingEntity(const sf::Texture * const texture,
											   			   const sf::Vector2f &position,
													       const sf::Vector2f &scale = sf::Vector2f(1.0f, 1.0f),
													       const float velocity = 50.0f);
	const unsigned int					createAnimatedEntity(const std::vector<const sf::Texture * const> &textures,
															 const sf::Time &duration,
															 const sf::Vector2f &position,
															 const sf::Vector2f &scale = sf::Vector2f(1.0f, 1.0f),
															 const float velocity = 50.0f);
	const unsigned int					createParticleEffect(const unsigned int maxParticleCount,
															 const bool respawn,
															 const sf::Texture * const texture,
															 const sf::Vector2f &position = sf::Vector2f(0.0f, 0.0f));

	void								addRenderComponent(const unsigned int id, RenderComponent *render);
	void								addTransformComponent(const unsigned int id, TransformComponent *xform);
	void								addAnimationComponent(const unsigned int id, AnimationComponent *anim);
	void								addMovementComponent(const unsigned int id, MovementComponent *mov);
	void								addEmitterComponent(const unsigned int id, EmitterComponent *emitter);
	void								addParticleComponent(const unsigned int id, ParticleComponent *particle);
	void								addTextComponent(const unsigned int id, TextComponent *text);

	void								removeRenderComponent(const unsigned int id);
	void								removeTransformComponent(const unsigned int id);
	void								removeAnimationComponent(const unsigned int id);
	void								removeMovementComponent(const unsigned int id);
	void								removeEmitterComponent(const unsigned int id);
	void								removeParticleComponent(const unsigned int id);
	void								removeTextComponent(const unsigned int id);

	unsigned int						entityCount;

	std::vector<RenderComponent *>		renderComponents;
	std::vector<TransformComponent *>	transformComponents;
	std::vector<MovementComponent *>	movementComponents;
	std::vector<ParticleComponent *>	particleComponents;
	std::vector<EmitterComponent *>		emitterComponents;
	std::vector<AnimationComponent *>	animationComponents;
	std::vector<TextComponent *>		textComponents;
	//std::vector<CollisionComponent *>	collisionComponents;
};