#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

bool																	ResourceManager::loadTexture(const std::string &path)
{
	sf::Texture	* const													texture = new sf::Texture();
	
	if (!texture->loadFromFile(path))
		return (false);
	_textures.insert(std::pair<const std::string, const sf::Texture * const>(path, texture));
	return (true);
}

void																	ResourceManager::unloadTexture(const std::string &id)
{
	std::map<const std::string, const sf::Texture * const>::iterator	it;

	if ((it = _textures.find(id)) != _textures.end())
	{
		delete (it->second);
		_textures.erase(it);
	}
}

const sf::Texture * const												ResourceManager::getTexture(const std::string &id) const
{
	if (_textures.find(id) == _textures.end())
		return (NULL);
	return (_textures.at(id));
}