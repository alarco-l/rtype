# pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class IRFCClient
{
public:
	enum Weapon
	{
		WEAPON1,
		WEAPON2,
		WEAPON3,
		WEAPONMAX
	};
	virtual void	sendHandshake() = 0;
	virtual void	sendMove(const sf::Vector2f &pos, const sf::Vector2f &direction) = 0; // 9bytes
	virtual void	sendShoot(Weapon weapon, unsigned int idAmmo, const sf::Vector2f &pos, const sf::Vector2f &direction) = 0; // 12bytes
	virtual void	sendCollision(unsigned int idClient, unsigned int idMonster, const sf::Vector2f &pos) = 0; // 9bytes
	virtual void	sendHitMonster(unsigned int idMonster, const sf::Vector2f &posMonster) = 0; // 7bytes
	virtual void	sendKillMonster(unsigned int idMonster, const sf::Vector2f &posMonster) = 0; // 7btytes
private:
	virtual void	createHandshakeData(unsigned int idClient = 0) = 0;
	//virtual bool	tryConnect(Socket &socket) = 0;
};
