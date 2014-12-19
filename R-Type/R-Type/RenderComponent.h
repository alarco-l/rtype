#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

struct															RenderComponent
{
	const sf::Texture											*texture;
	sf::VertexArray												vertices;
};