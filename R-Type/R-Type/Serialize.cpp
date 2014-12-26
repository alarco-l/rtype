#include "Serialize.h"


Serialize::Serialize()
{
}

Serialize::~Serialize()
{
}

void		*Serialize::createSendHandshake(unsigned int idClient) //6bytes
{
	return (NULL);
}

void		*Serialize::createSendMove(const sf::Vector2f &pos, const sf::Vector2f &direction) // 9bytes
{
	return (NULL);
}

void		*Serialize::createSendShoot(IRFCClient::Weapon weapon, unsigned int idAmmo, const sf::Vector2f &pos, const sf::Vector2f &direction) // 12bytes
{
	return (NULL);
}

void		*Serialize::createSendCollision(unsigned int idClient, unsigned int idMonster, const sf::Vector2f &pos) // 9bytes
{
	return (NULL);
}

void		*Serialize::createSendHitMonster(unsigned int idMonster, const sf::Vector2f &posMonster) // 7bytes
{
	return (NULL);
}

void		*Serialize::createSendKillMonster(unsigned int idMonster, const sf::Vector2f &posMonster) // 7btytes
{
	return (NULL);
}
