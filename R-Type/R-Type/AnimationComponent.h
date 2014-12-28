#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Texture.hpp>

struct														AnimationComponent
{
	sf::Time												maxLifetime;
	sf::Time												lifetime;
	std::vector<const sf::Texture * const>					animations;
	std::vector<const sf::Texture * const>::const_iterator	currentAnimation;
	bool													restart;
};