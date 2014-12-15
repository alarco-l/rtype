#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

struct															RenderComponent
{
	RenderComponent(const sf::Texture * const tex) :
		texture(tex), vertices(sf::Quads, 4)
	{
		sf::Vector2f											textureSize(texture->getSize());

		vertices[0].texCoords = sf::Vector2f(0.0f, 0.0f);
		vertices[1].texCoords = sf::Vector2f(textureSize.x, 0.0f);
		vertices[2].texCoords = sf::Vector2f(textureSize.x, textureSize.y);
		vertices[3].texCoords = sf::Vector2f(0.0f, textureSize.y);

		vertices[0].position = vertices[0].texCoords;
		vertices[1].position = vertices[1].texCoords;
		vertices[2].position = vertices[2].texCoords;
		vertices[3].position = vertices[3].texCoords;
	}

	const sf::Texture											*texture;
	sf::VertexArray												vertices;
};