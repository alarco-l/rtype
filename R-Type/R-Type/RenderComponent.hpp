#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

struct															RenderComponent
{
	RenderComponent(const sf::Texture * const _texture = NULL, const sf::Vector2f &scale = sf::Vector2f(1.0f, 1.0f))
	: texture(_texture), size(texture->getSize().x * scale.x, texture->getSize().y * scale.y)
	{
		sf::Vector2f							textureSize(static_cast<float>(texture->getSize().x), static_cast<float>(texture->getSize().y));

		vertices.setPrimitiveType(sf::Quads);
		vertices.append(sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f)));
		vertices.append(sf::Vertex(sf::Vector2f(size.x, 0.0f), sf::Vector2f(textureSize.x, 0.0f)));
		vertices.append(sf::Vertex(sf::Vector2f(size.x, size.y), sf::Vector2f(textureSize.x, textureSize.y)));
		vertices.append(sf::Vertex(sf::Vector2f(0.0f, size.y), sf::Vector2f(0.0f, textureSize.y)));
	}

	const sf::Texture											*texture;
	sf::Vector2f												size;
	sf::VertexArray												vertices;
};