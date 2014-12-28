#include "ComponentFactory.h"

RenderComponent					*ComponentFactory::createRenderComponent(const sf::Texture * const tex,
	const unsigned int plane,
	const sf::Color &color)
{
	RenderComponent				*render = new RenderComponent();

	render->texture = tex;
	render->vertices = sf::VertexArray(sf::Quads, 4);
	render->color = color;
	render->plane = plane;

	return (render);
}

TransformComponent				*ComponentFactory::createTransformComponent(const sf::Vector2f &size,
	const sf::Vector2f &pos,
	const sf::Vector2f &sca,
	const float rot)
{
	TransformComponent			*xform = new TransformComponent();


	xform->size = size;
	xform->position = pos;
	xform->scale = sca;
	xform->rotation = rot;
	xform->origin = sf::Vector2f();

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
	anim->restart = true;

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

EmitterComponent				*ComponentFactory::createEmitterComponent(const bool respawn,
	const sf::Vector2f &lifetimeInterval,
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

ParticleComponent				*ComponentFactory::createParticleComponent(const sf::Time &lifetime, unsigned int emitterId)
{
	ParticleComponent			*particle = new ParticleComponent();

	particle->emitterId = emitterId;
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

ScrollComponent					*ComponentFactory::createScrollComponent(const float speed, const sf::Vector2f &direction)
{
	ScrollComponent				*scroll = new ScrollComponent();

	scroll->speed = speed;
	scroll->direction = direction;

	return (scroll);
}

ProjectileComponent				*ComponentFactory::createProjectileComponent(const unsigned int damage, const unsigned int owner)
{
	ProjectileComponent			*proj = new ProjectileComponent();

	proj->damage = damage;
	proj->owner = owner;

	return (proj);
}

WeaponComponent					*ComponentFactory::createWeaponComponent(const sf::Time &maxCooldown, const unsigned int owner, const unsigned int projectileType)
{
	WeaponComponent				*weapon = new WeaponComponent();

	weapon->maxCooldown = maxCooldown;
	weapon->cooldown = sf::Time::Zero;
	weapon->fire = false;
	weapon->owner = owner;
	weapon->projectileType = projectileType;

	return (weapon);
}

ParentComponent					*ComponentFactory::createParentComponent(const unsigned int id, const float degree)
{
	ParentComponent				*parent = new ParentComponent();

	parent->id = id;
	parent->degree = degree;

	return (parent);
}

ChildrenComponent				*ComponentFactory::createChildrenComponent(const std::set<unsigned int> &id, const float degree)
{
	ChildrenComponent			*children = new ChildrenComponent();

	children->id = id;
	children->degree = degree;

	return (children);
}

InfoComponent					*ComponentFactory::createInfoComponent(const unsigned int life, const unsigned int shield, const unsigned int team, const std::vector<const sf::Texture * const> &deathAnimation, const sf::Time &maxLifetime)
{
	InfoComponent				*info = new InfoComponent();

	info->life = life;
	info->shield = shield;
	info->team = team;
	info->score = 0;
	info->damageReceived = 0;
	info->deathAnimation = deathAnimation;
	info->maxLifetime = maxLifetime;
	info->dead = false;

	return (info);
}

GrowComponent					*ComponentFactory::createGrowComponent(const sf::Vector2f &direction, float speed, const sf::Vector2f &limit)
{
	GrowComponent				*grow = new GrowComponent();

	grow->direction = direction;
	grow->speed = speed;
	grow->limit = limit;

	return (grow);
}

TimerComponent					*ComponentFactory::createTimerComponent(const sf::Time &countdown)
{
	TimerComponent				*timer = new TimerComponent();

	timer->countdown = countdown;

	return (timer);
}