#include "World.h"

World::World() :
	entityCount(0)
{
}

World::~World()
{
	for (unsigned int i = 0; i != entityCount; ++i)
	{
		if (renderComponents[i])
			delete (renderComponents[i]);
		if (transformComponents[i])
			delete (transformComponents[i]);
		if (animationComponents[i])
			delete (animationComponents[i]);
		if (movementComponents[i])
			delete (movementComponents[i]);
		if (emitterComponents[i])
			delete (emitterComponents[i]);
		if (particleComponents[i])
			delete (particleComponents[i]);
	}
}

const unsigned int						World::createStaticEntity(const sf::Texture * const texture, const sf::Vector2f &position, const sf::Vector2f &scale)
{
	RenderComponent						*render = ComponentFactory::createRenderComponent(texture);
	TransformComponent					*xform = ComponentFactory::createTransformComponent(position, scale);

	renderComponents.push_back(render);
	transformComponents.push_back(xform);
	movementComponents.push_back(NULL);
	particleComponents.push_back(NULL);
	emitterComponents.push_back(NULL);
	animationComponents.push_back(NULL);
	textComponents.push_back(NULL);
//	collisionComponents.push_back(NULL);

	return (entityCount++);
}

const unsigned int						World::createMovingEntity(const sf::Texture * const texture, const sf::Vector2f &position, const sf::Vector2f &scale, const float velocity)
{
	RenderComponent						*render = ComponentFactory::createRenderComponent(texture);
	TransformComponent					*xform = ComponentFactory::createTransformComponent(position, scale);
	MovementComponent					*mov = ComponentFactory::createMovementComponent(velocity, sf::Vector2f(1.0f, 0.0f));

	renderComponents.push_back(render);
	transformComponents.push_back(xform);
	movementComponents.push_back(mov);
	particleComponents.push_back(NULL);
	emitterComponents.push_back(NULL);
	animationComponents.push_back(NULL);
	textComponents.push_back(NULL);
	//collisionComponents.push_back(NULL);

	return (entityCount++);
}

const unsigned int						World::createAnimatedEntity(const std::vector<const sf::Texture * const> &textures, const sf::Time &duration, const sf::Vector2f &position, const sf::Vector2f &scale, const float velocity)
{
	RenderComponent						*render = ComponentFactory::createRenderComponent(textures[0]);
	TransformComponent					*xform = ComponentFactory::createTransformComponent(position, scale);
	MovementComponent					*mov = ComponentFactory::createMovementComponent(velocity, sf::Vector2f(1.0f, 0.0f));
	AnimationComponent					*anim = ComponentFactory::createAnimationComponent(textures, duration);

	renderComponents.push_back(render);
	transformComponents.push_back(xform);
	movementComponents.push_back(mov);
	animationComponents.push_back(anim);
	particleComponents.push_back(NULL);
	emitterComponents.push_back(NULL);
	textComponents.push_back(NULL);
	//collisionComponents.push_back(NULL);
	
	return (entityCount++);
}

const unsigned int						World::createParticleEffect(const unsigned int maxParticleCount, const bool respawn, const sf::Texture * const texture, const sf::Vector2f &position)
{
	unsigned int						emitterId;
	std::vector<unsigned int>			particleId;
	EmitterComponent					*emitter = ComponentFactory::createEmitterComponent(sf::Vector2f(1.0f, 8.0f), respawn, sf::Vector2f(0.0f, 360.0f), sf::Vector2f(30.0f, 100.0f), sf::Vector2f(0.25f, 0.25f));
	TransformComponent					*xform = ComponentFactory::createTransformComponent(position);

	emitterComponents.push_back(emitter);
	transformComponents.push_back(xform);
	movementComponents.push_back(NULL);
	particleComponents.push_back(NULL);
	renderComponents.push_back(NULL);
	animationComponents.push_back(NULL);
	textComponents.push_back(NULL);
//	collisionComponents.push_back(NULL);

	emitterId = entityCount;
	++entityCount;

	for (unsigned int i = 0; i != maxParticleCount; ++i)
	{
		RenderComponent					*render = ComponentFactory::createRenderComponent(texture);
		TransformComponent				*xform = ComponentFactory::createTransformComponent(position);
		MovementComponent				*mov = ComponentFactory::createMovementComponent(50.0f, sf::Vector2f(1.0f, 0.0f));
		ParticleComponent				*particle = ComponentFactory::createParticleComponent(sf::Time::Zero);

		particle->emitterId = emitterId;

		renderComponents.push_back(render);
		transformComponents.push_back(xform);
		movementComponents.push_back(mov);
		particleComponents.push_back(particle);
		emitterComponents.push_back(NULL);
		animationComponents.push_back(NULL);
		textComponents.push_back(NULL);
	//	collisionComponents.push_back(NULL);

		particleId.push_back(entityCount);
		++entityCount;
	}

	emitter->particleId = particleId;

	return (emitterId);
}

void									World::addRenderComponent(const unsigned int id, RenderComponent *render)
{
	renderComponents[id] = render;
}

void									World::addTransformComponent(const unsigned int id, TransformComponent *xform)
{
	transformComponents[id] = xform;
}

void									World::addAnimationComponent(const unsigned int id, AnimationComponent *anim)
{
	animationComponents[id] = anim;
}

void									World::addMovementComponent(const unsigned int id, MovementComponent *mov)
{
	movementComponents[id] = mov;
}

void									World::addEmitterComponent(const unsigned int id, EmitterComponent *emitter)
{
	emitterComponents[id] = emitter;
}

void									World::addParticleComponent(const unsigned int id, ParticleComponent *particle)
{
	particleComponents[id] = particle;
}

void									World::addTextComponent(const unsigned int id, TextComponent *text)
{
	textComponents[id] = text;
}

void									World::removeRenderComponent(const unsigned int id)
{
	delete (renderComponents[id]);
	renderComponents[id] = NULL;
}

void									World::removeTransformComponent(const unsigned int id)
{
	delete (transformComponents[id]);
	transformComponents[id] = NULL;
}

void									World::removeAnimationComponent(const unsigned int id)
{
	delete (animationComponents[id]);
	animationComponents[id] = NULL;
}

void									World::removeMovementComponent(const unsigned int id)
{
	delete (movementComponents[id]);
	movementComponents[id] = NULL;
}

void									World::removeEmitterComponent(const unsigned int id)
{
	delete (emitterComponents[id]);
	emitterComponents[id] = NULL;
}

void									World::removeParticleComponent(const unsigned id)
{
	delete (particleComponents[id]);
	particleComponents[id] = NULL;
}

void									World::removeTextComponent(const unsigned int id)
{
	delete (textComponents[id]);
	textComponents[id] = NULL;
}