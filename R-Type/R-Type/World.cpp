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
		if (collisionComponents[i])
			delete (collisionComponents[i]);
	}
}

/*const unsigned int						World::createStaticEntity(const sf::Texture * const texture, const sf::Vector2f &position, const sf::Vector2f &scale)
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
	collisionComponents.push_back(NULL);

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
	collisionComponents.push_back(NULL);

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
	collisionComponents.push_back(NULL);
	
	return (entityCount++);
}
*/
const unsigned int						World::createParticleEffect(const unsigned int maxParticleCount, const bool respawn, const sf::Texture * const texture, const sf::Vector2f &position, const sf::Vector2f &lifeTime, const sf::Vector2f &scale)
{
	unsigned int						emitterId;
	std::vector<unsigned int>			particleId;

	emitterId = this->createEmptyEntity();
	this->addEmitterComponent(emitterId, ComponentFactory::createEmitterComponent(lifeTime, respawn, sf::Vector2f(180.0f, 185.0f)));
	this->addTransformComponent(emitterId, ComponentFactory::createTransformComponent(sf::Vector2f(), position));

	for (unsigned int i = 0; i != maxParticleCount; ++i)
	{
		unsigned int					id;
		id = this->createEmptyEntity();
		this->addRenderComponent(id, ComponentFactory::createRenderComponent(texture, 2));
		this->addTransformComponent(id, ComponentFactory::createTransformComponent(sf::Vector2f(texture->getSize()), position, scale));
		this->addMovementComponent(id, ComponentFactory::createMovementComponent(50.0f, sf::Vector2f(1.0f, 0.0f)));
		this->addParticleComponent(id, ComponentFactory::createParticleComponent(sf::Time::Zero, emitterId));

		particleId.push_back(id);
	}
	this->emitterComponents[emitterId]->particleId = particleId;

	return (emitterId);
}

const unsigned int						World::createEmptyEntity()
{
	renderComponents.push_back(NULL);
	animationComponents.push_back(NULL);
	transformComponents.push_back(NULL);
	movementComponents.push_back(NULL);
	spinComponents.push_back(NULL);
	emitterComponents.push_back(NULL);
	particleComponents.push_back(NULL);
	textComponents.push_back(NULL);
	collisionComponents.push_back(NULL);
	scrollComponent.push_back(NULL);

	return (entityCount++);
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

void									World::addSpinComponent(const unsigned int id, SpinComponent *spin)
{
	spinComponents[id] = spin;
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

void									World::addCollisionComponent(const unsigned int id, CollisionComponent *col)
{
	collisionComponents[id] = col;
}

void									World::addScrollComponent(const unsigned int id, ScrollComponent *scroll)
{
	scrollComponent[id] = scroll;
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

void									World::removeSpinComponent(const unsigned int id)
{
	delete (spinComponents[id]);
	spinComponents[id] = NULL;
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

void									World::removeCollisionComponent(const unsigned int id)
{
	delete (collisionComponents[id]);
	collisionComponents[id] = NULL;
}

void									World::removeScrollComponent(const unsigned int id)
{
	delete (scrollComponent[id]);
	scrollComponent[id] = NULL;
}