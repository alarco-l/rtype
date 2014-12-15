#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Texture.hpp>

struct														AnimationComponent
{
	AnimationComponent(const std::vector<const sf::Texture * const> &anims,
					   const sf::Time &_maxLifetime) :
		maxLifetime(_maxLifetime), lifetime(_maxLifetime), animations(anims), currentAnimation(animations.begin())
	{
	}

	sf::Time												maxLifetime;
	sf::Time												lifetime;	
	std::vector<const sf::Texture * const>					animations;
	std::vector<const sf::Texture * const>::const_iterator	currentAnimation;
};