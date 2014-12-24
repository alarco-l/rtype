#include "Serialize.h"


Serialize::Serialize()
{
}

Serialize::~Serialize()
{
}

void		*Serialize::createSendHandshake(unsigned int idClient) //6bytes
{
	char	tmp[5];
	tmp[0] = '1';
	tmp[1] = '0';
	tmp[2] = '0';
	tmp[3] = '0';
}

void		*Serialize::createSendMove(const sf::Vector2f &pos, const sf::Vector2f &direction) // 9bytes
{

}

void		*Serialize::createSendShoot(IRFCClient::Weapon weapon, unsigned int idAmmo, const sf::Vector2f &pos, const sf::Vector2f &direction) // 12bytes
{

}

void		*Serialize::createSendCollision(unsigned int idClient, unsigned int idMonster, const sf::Vector2f &pos) // 9bytes
{

}

void		*Serialize::createSendHitMonster(unsigned int idMonster, const sf::Vector2f &posMonster) // 7bytes
{

}

void		*Serialize::createSendKillMonster(unsigned int idMonster, const sf::Vector2f &posMonster) // 7btytes
{

}
