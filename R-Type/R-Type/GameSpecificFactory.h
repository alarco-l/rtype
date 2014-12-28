#pragma once

#include "World.h"
#include "ResourceManager.h"
#include "GameEnums.h"

class										GameSpecificFactory
{
public:
	typedef void							(GameSpecificFactory::*projectileCreator)(unsigned int *id, const unsigned int weapon, World &world, const sf::Vector2u &screenSize);

	GameSpecificFactory(ResourceManager &resourceManager);

	// MENUS

	void									createMainMenu(unsigned int *id, World &world, const sf::Vector2u &screenSize);
	void									createLoadMenu(unsigned int *id, World &world, const sf::Vector2u &screenSize);
	void									createPauseMenu(unsigned int *id, World &world, const sf::Vector2u &screenSize);
	void									createEndMenu(unsigned int *id, World &world, const sf::Vector2u &screenSize, const std::string &result);

	// GAME

	void									createGameBackground(unsigned int *id, World &world, const sf::Vector2u &screenSize);
	void									createHUD(unsigned int *id, World &world, const sf::Vector2u &screenSize);
	void									createPlayer(unsigned int *id, World &world);

	//PROJECTILES

	projectileCreator						createProjectile[2];
	void									createMissileProjectile(unsigned int *id, const unsigned int weapon, World &world, const sf::Vector2u &screenSize);
	void									createLaserProjectile(unsigned int *id, const unsigned int weapon, World &world, const sf::Vector2u &screenSize);
private:
	GameSpecificFactory();

	ResourceManager							&_resourceManager;
};