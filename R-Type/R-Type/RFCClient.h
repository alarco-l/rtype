# pragma once

# include "IRFCClient.h"
# include "Serialize.h"

class RFCClient : public IRFCClient
{
public:
	RFCClient();
	~RFCClient();
	void	sendHandshate(); //6bytes
	void	sendMove(const sf::Vector2f &pos, const sf::Vector2f &direction); // 9bytes
	void	sendShoot(Weapon weapon, unsigned int idAmmo, const sf::Vector2f &pos, const sf::Vector2f &direction); // 12bytes
	void	sendCollision(unsigned int idClient, unsigned int idMonster, const sf::Vector2f &pos); // 9bytes
	void	sendHitMonster(unsigned int idMonster, const sf::Vector2f &posMonster); // 7bytes
	void	sendKillMonster(unsigned int idMonster, const sf::Vector2f &posMonster); // 7btytes

private:

	bool	_handshate;
	bool	_isConnect;
	ASocket	*_socket;
};