#include "ComponentFactory.h"

ComponentFactory::~ComponentFactory()
{
}

RenderComponent					*ComponentFactory::createRenderComponent(const sf::Texture * const tex)
{
	RenderComponent				*render = new RenderComponent();
	sf::Vector2f				textureSize(tex->getSize());

	render->texture = tex;
	render->vertices = sf::VertexArray(sf::Quads, 4);

	render->vertices[0].texCoords = sf::Vector2f(0.0f, 0.0f);
	render->vertices[1].texCoords = sf::Vector2f(textureSize.x, 0.0f);
	render->vertices[2].texCoords = sf::Vector2f(textureSize.x, textureSize.y);
	render->vertices[3].texCoords = sf::Vector2f(0.0f, textureSize.y);

	render->vertices[0].position = render->vertices[0].texCoords;
	render->vertices[1].position = render->vertices[1].texCoords;
	render->vertices[2].position = render->vertices[2].texCoords;
	render->vertices[3].position = render->vertices[3].texCoords;

	return (render);
}

TransformComponent				*ComponentFactory::createTransformComponent(const sf::Vector2f &pos, const sf::Vector2f &sca, const float rot)
{
	TransformComponent			*xform = new TransformComponent();

	xform->position = pos;
	xform->scale = sca;
	xform->rotation = rot;
	xform->origin = sf::Vector2f(0.0f, 0.0f);

	return (xform);
}

AnimationComponent				*ComponentFactory::createAnimationComponent(const std::vector<const sf::Texture * const> &anims,
																			const sf::Time &maxLifetime)
{
	AnimationComponent			*anim = new AnimationComponent();

	anim->maxLifetime = maxLifetime;
	anim->lifetime = maxLifetime;
	anim->animations = anims;
	anim->currentAnimation = anim->animations.begin();

	return (anim);
}

MovementComponent				*ComponentFactory::createMovementComponent(const float vel,
																		   const sf::Vector2f &dir)
{
	MovementComponent			*mov = new MovementComponent();

	mov->velocity = vel;
	mov->direction = dir;
	return (mov);
}

EmitterComponent				*ComponentFactory::createEmitterComponent(const sf::Vector2f &lifetimeInterval,
																		  const bool respawn,
																		  const sf::Vector2f &propagationInterval,
																		  const sf::Vector2f &velocityInterval,
																		  const sf::Vector2f &scaleInterval)
{
	EmitterComponent			*emitter = new EmitterComponent();

	emitter->respawn = respawn;
	emitter->lifetimeInterval = lifetimeInterval;
	emitter->propagationInterval = propagationInterval;
	emitter->velocityInterval = velocityInterval;
	emitter->scaleInterval = scaleInterval;

	return (emitter);
}

ParticleComponent				*ComponentFactory::createParticleComponent(const sf::Time &lifetime)
{
	ParticleComponent			*particle = new ParticleComponent();

	particle->maxLifetime = lifetime;
	particle->lifetime = lifetime;

	return (particle);
}
