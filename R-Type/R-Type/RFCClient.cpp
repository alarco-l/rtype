#include "RFCClient.h"

RFCClient::RFCClient() {
	_handshate = false;
	_isConnect = false;
}

RFCClient::~RFCClient() {}

void	RFCClient::sendHandshate() // 6bytes
{
	if (_socket->isConnect() == true) {
		_socket->send(Serialize::createSendHandshake());
	}
}

void	RFCClient::sendMove(const sf::Vector2f &pos, const sf::Vector2f &direction) // 9bytes
{
	if (_socket->isConnect() == true) {
		_socket->send(Serialize::createSendMove(pos,direction));
	}
}

void	RFCClient::sendShoot(RFCClient::Weapon weapon, unsigned int idAmmo, const sf::Vector2f &pos, const sf::Vector2f &direction) // 12bytes
{
	if (_socket->isConnect() == true) {
		_socket->send(Serialize::createSendShoot(weapon, idAmmo, pos, direction));
	}
}

void	RFCClient::sendCollision(unsigned int idClient, unsigned int idMonster, const sf::Vector2f &pos) // 9bytes
{
	if (_socket->isConnect() == true) {
		_socket->send(Serialize::createSendCollision(idClient, idMonster, pos));
	}
}

void	RFCClient::sendHitMonster(unsigned int idMonster, const sf::Vector2f &posMonster) // 7bytes
{
	if (_socket->isConnect() == true) {
		_socket->send(Serialize::createSendHitMonster(idMonster, posMonster));
	}
}

void	RFCClient::sendKillMonster(unsigned int idMonster, const sf::Vector2f &posMonster) // 7btytes
{
	if (_socket->isConnect() == true) {
		_socket->send(Serialize::createSendKillMonster(idMonster, posMonster));
	}
}
