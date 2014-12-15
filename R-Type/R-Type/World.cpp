#include "World.h"

World::World() : entityCount(0)
{
}

World::~World()
{
}

void									World::createStaticEntity(const sf::Texture * const texture, const sf::Vector2f &position, const sf::Vector2f &scale)
{
	RenderComponent						*render = new RenderComponent(texture);
	TransformComponent					*xform = new TransformComponent(position, scale);

	renderComponents.push_back(render);
	transformComponents.push_back(xform);
	movementComponents.push_back(NULL);
	particleComponents.push_back(NULL);
	emitterComponents.push_back(NULL);
	animationComponents.push_back(NULL);
	collisionComponents.push_back(NULL);
	++entityCount;
}

void									World::createEntity(const sf::Texture * const texture, const sf::Vector2f &position, const sf::Vector2f &scale, const float velocity)
{
	RenderComponent						*render = new RenderComponent(texture);
	TransformComponent					*xform = new TransformComponent(position, scale);
	MovementComponent					*mov = new MovementComponent(velocity, sf::Vector2f(1.0f, 0.0f));

	renderComponents.push_back(render);
	transformComponents.push_back(xform);
	movementComponents.push_back(mov);
	particleComponents.push_back(NULL);
	emitterComponents.push_back(NULL);
	animationComponents.push_back(NULL);
	collisionComponents.push_back(NULL);
	++entityCount;
}

void									World::createAnimatedEntity(const std::vector<const sf::Texture * const> &textures, const sf::Time &duration, const sf::Vector2f &position, const sf::Vector2f &scale, const float velocity)
{
	RenderComponent						*render = new RenderComponent(textures[0]);
	TransformComponent					*xform = new TransformComponent(position, scale);
	MovementComponent					*mov = new MovementComponent(velocity, sf::Vector2f(1.0f, 0.0f));
	AnimationComponent					*anim = new AnimationComponent(textures, duration);

	renderComponents.push_back(render);
	transformComponents.push_back(xform);
	movementComponents.push_back(mov);
	animationComponents.push_back(anim);
	particleComponents.push_back(NULL);
	emitterComponents.push_back(NULL);
	collisionComponents.push_back(NULL);
	
	++entityCount;
}

void									World::createParticleEffect(const unsigned int maxParticleCount, const bool respawn, const sf::Texture * const texture, const sf::Vector2f &position)
{
	unsigned int						emitterId;
	std::vector<unsigned int>			particleId;
	EmitterComponent					*emitter = new EmitterComponent(sf::Vector2f(1.0f, 8.0f), respawn, sf::Vector2f(0.0f, 360.0f), sf::Vector2f(30.0f, 100.0f), sf::Vector2f(0.25f, 0.25f));
	TransformComponent					*xform = new TransformComponent(position);

	emitterComponents.push_back(emitter);
	transformComponents.push_back(xform);
	movementComponents.push_back(NULL);
	particleComponents.push_back(NULL);
	renderComponents.push_back(NULL);
	animationComponents.push_back(NULL);
	collisionComponents.push_back(NULL);

	emitterId = entityCount;
	++entityCount;

	for (unsigned int i = 0; i != maxParticleCount; ++i)
	{
		RenderComponent					*render = new RenderComponent(texture);
		TransformComponent				*xform = new TransformComponent(position);
		MovementComponent				*mov = new MovementComponent(50.0f, sf::Vector2f(1.0f, 0.0f));
		ParticleComponent				*particle = new ParticleComponent(sf::Time::Zero);

		particle->emitterId = emitterId;

		renderComponents.push_back(render);
		transformComponents.push_back(xform);
		movementComponents.push_back(mov);
		particleComponents.push_back(particle);
		emitterComponents.push_back(NULL);
		animationComponents.push_back(NULL);
		collisionComponents.push_back(NULL);

		particleId.push_back(entityCount);
		++entityCount;
	}

	emitter->particleId = particleId;
}
