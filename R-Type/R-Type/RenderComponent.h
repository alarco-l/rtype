#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Transform.hpp>

struct															RenderComponent
{
	const sf::Texture											*texture;
	sf::VertexArray												vertices;
	unsigned int												plane;
	sf::Color													color;
	sf::Transform												transform;
};