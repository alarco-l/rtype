#pragma once

#include "Components.h"

class							ComponentFactory
{
public:
	static RenderComponent		*createRenderComponent(const sf::Texture * const tex,
		const unsigned int plane = 0,
		const sf::Color &color = sf::Color::White);

	static TransformComponent	*createTransformComponent(const sf::Vector2f &size,
		const sf::Vector2f &pos,
		const sf::Vector2f &sca = sf::Vector2f(1.0f, 1.0f),
		const float rot = 0.0f);

	static AnimationComponent	*createAnimationComponent(const std::vector<const sf::Texture * const> &anims,
		const sf::Time &maxLifetime);

	static MovementComponent	*createMovementComponent(const float vel,
		const sf::Vector2f &dir);

	static SpinComponent		*createSpinComponent(const float speed,
		const int direction);

	static EmitterComponent		*createEmitterComponent(const bool respawn,
		const sf::Vector2f &lifetimeInterval = sf::Vector2f(0.0f, 3.0f),
		const sf::Vector2f &propagationInterval = sf::Vector2f(0.0f, 360.0f),
		const sf::Vector2f &velocityInterval = sf::Vector2f(30.0f, 100.0f),
		const sf::Vector2f &scaleInterval = sf::Vector2f(1.0f, 1.0f));

	static ParticleComponent	*createParticleComponent(const sf::Time &lifetime, unsigned int emitterId);

	static TextComponent		*createTextComponent(const std::string &string,
		const sf::Font * const font,
		bool centered = false,
		bool hightlighted = false,
		const unsigned int size = 30,
		const sf::Color &color = sf::Color::White);

	static CollisionComponent	*createCollisionComponent();

	static ScrollComponent		*createScrollComponent(const float speed,
		const sf::Vector2f &direction = sf::Vector2f(-1.0f, 0.0f));

	static ProjectileComponent	*createProjectileComponent(const unsigned int damage,
		const unsigned int owner);

	static WeaponComponent		*createWeaponComponent(const sf::Time &maxCooldown,
		const unsigned int owner,
		const unsigned int projectileType);

	static ParentComponent		*createParentComponent(const unsigned int id,
		const float degree = 1.0f);

	static ChildrenComponent	*createChildrenComponent(const std::set<unsigned int> &id,
		const float degree = 1.0f);

	static InfoComponent		*createInfoComponent(const unsigned int life,
		const unsigned int shield,
		const unsigned int team,
		const std::vector<const sf::Texture * const> &deathAnimation = std::vector<const sf::Texture * const>(),
		const sf::Time &maxLifetime = sf::seconds(1));

	static GrowComponent		*createGrowComponent(const sf::Vector2f &direction, float speed, const sf::Vector2f &limit = sf::Vector2f(0.0f, 0.0f));

	static TimerComponent		*createTimerComponent(const sf::Time &timer);
private:
	ComponentFactory();
};