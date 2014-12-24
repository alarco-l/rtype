# pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "IRFCClient.h"

class Serialize
{
public:
	~Serialize();
	static void		*createSendHandshake(unsigned int idClient = 0); //6bytes
	static void		*createSendMove(const sf::Vector2f &pos, const sf::Vector2f &direction); // 9bytes
	static void		*createSendShoot(IRFCClient::Weapon weapon, unsigned int idAmmo, const sf::Vector2f &pos, const sf::Vector2f &direction); // 12bytes
	static void		*createSendCollision(unsigned int idClient, unsigned int idMonster, const sf::Vector2f &pos); // 9bytes
	static void		*createSendHitMonster(unsigned int idMonster, const sf::Vector2f &posMonster); // 7bytes
	static void		*createSendKillMonster(unsigned int idMonster, const sf::Vector2f &posMonster); // 7btytes

private:
	Serialize();
};
