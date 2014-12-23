#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Color.hpp>

struct															RenderComponent
{
	const sf::Texture											*texture;
	sf::VertexArray												vertices;
	sf::Color													color;
};