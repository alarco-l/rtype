#pragma once

#include <vector>

#include "ComponentFactory.h"

class									World
{
public:
	World();
	~World();

	const unsigned int					createParticleEffect(const unsigned int maxParticleCount,
															 const bool respawn,
															 const sf::Texture * const texture,
															 const sf::Vector2f &position,
															 const sf::Vector2f &scale = sf::Vector2f(1,1));

	const unsigned int					createEmptyEntity();

	void								addRenderComponent(const unsigned int id, RenderComponent *render);
	void								addTransformComponent(const unsigned int id, TransformComponent *xform);
	void								addAnimationComponent(const unsigned int id, AnimationComponent *anim);
	void								addMovementComponent(const unsigned int id, MovementComponent *mov);
	void								addSpinComponent(const unsigned int id, SpinComponent *spin);
	void								addEmitterComponent(const unsigned int id, EmitterComponent *emitter);
	void								addParticleComponent(const unsigned int id, ParticleComponent *particle);
	void								addTextComponent(const unsigned int id, TextComponent *text);
	void								addCollisionComponent(const unsigned int id, CollisionComponent *col);
	void								addScrollComponent(const unsigned int id, ScrollComponent *scroll);

	void								removeRenderComponent(const unsigned int id);
	void								removeTransformComponent(const unsigned int id);
	void								removeAnimationComponent(const unsigned int id);
	void								removeMovementComponent(const unsigned int id);
	void								removeSpinComponent(const unsigned int id);
	void								removeEmitterComponent(const unsigned int id);
	void								removeParticleComponent(const unsigned int id);
	void								removeTextComponent(const unsigned int id);
	void								removeCollisionComponent(const unsigned int id);
	void								removeScrollComponent(const unsigned int id);

	unsigned int						entityCount;

	std::vector<RenderComponent *>		renderComponents;
	std::vector<TransformComponent *>	transformComponents;
	std::vector<MovementComponent *>	movementComponents;
	std::vector<SpinComponent *>		spinComponents;
	std::vector<ParticleComponent *>	particleComponents;
	std::vector<EmitterComponent *>		emitterComponents;
	std::vector<AnimationComponent *>	animationComponents;
	std::vector<TextComponent *>		textComponents;
	std::vector<CollisionComponent *>	collisionComponents;
	std::vector<ScrollComponent *>		scrollComponents;
};