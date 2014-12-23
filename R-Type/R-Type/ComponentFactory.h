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

	static EmitterComponent		*createEmitterComponent(const sf::Vector2f &lifetimeInterval,
														const bool respawn,
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

	static ScrollComponent		*createScrollComponent(const float speed, const sf::Vector2f &direction = sf::Vector2f(-1.0f, 0.0f));

private:
	ComponentFactory();
};