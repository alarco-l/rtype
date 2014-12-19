#pragma once

#include <string>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

struct						TextComponent
{
	std::string				string;
	sf::Color				color;
	unsigned int			size;
	sf::Font				*font;
};