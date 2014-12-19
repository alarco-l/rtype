#pragma once

#include <string>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

struct						TextComponent
{
	std::string				string;
	const sf::Font			*font;
	unsigned int			size;
	sf::Color				color;
};