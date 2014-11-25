#pragma once

#include <map>

#include <SFML/Graphics/Texture.hpp>

class														ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	bool													loadTexture(const std::string &path);
	void													unloadTexture(const std::string &id);
	const sf::Texture * const								getTexture(const std::string &id) const;
private:
	ResourceManager(const ResourceManager &rhs);
	const ResourceManager &operator=(const ResourceManager &rhs);

	std::map<const std::string, const sf::Texture * const>	_textures;
};