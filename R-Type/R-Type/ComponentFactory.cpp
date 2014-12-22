#include "ComponentFactory.h"

RenderComponent					*ComponentFactory::createRenderComponent(const sf::Texture * const tex,
																		 const sf::Color &color)
{
	RenderComponent				*render = new RenderComponent();
	sf::Vector2f				textureSize(tex->getSize());

	render->texture = tex;
	render->vertices = sf::VertexArray(sf::Quads, 4);
	render->color = color;

	return (render);
}

TransformComponent				*ComponentFactory::createTransformComponent(const sf::Vector2f &size,
																			const sf::Vector2f &pos,
																			const sf::Vector2f &sca,
																			const float rot)
{
	TransformComponent			*xform = new TransformComponent();

	xform->position = pos;
	xform->scale = sca;
	xform->rotation = rot;
	xform->origin = sf::Vector2f(0.0f, 0.0f);
	xform->size = size;

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

SpinComponent					*ComponentFactory::createSpinComponent(const float speed,
																	   const int direction)
{
	SpinComponent				*spin = new SpinComponent();

	spin->speed = speed;
	spin->direction = direction;
	return (spin);
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

TextComponent					*ComponentFactory::createTextComponent(const std::string &string,
																	   const sf::Font * const font,
																	   bool centered,
																	   bool highlighted,
																	   const unsigned int size,
																	   const sf::Color &color)
{
	TextComponent				*txt = new TextComponent();

	txt->string = string;
	txt->font = font;
	txt->centered = centered;
	txt->highlighted = highlighted;
	txt->size = size;
	txt->color = color;

	return (txt);
}

CollisionComponent				*ComponentFactory::createCollisionComponent()
{
	CollisionComponent			*col = new CollisionComponent();

	return (col);
}