# include <cstring>
#include "RFCClient.h"


RFCClient::RFCClient() {
	_handshate = false;
	_isConnect = false;
	_id[PLAYER1] = 0;
	_id[PLAYER2] = 0;
	_id[PLAYER3] = 0;
	_id[PLAYER4] = 0;
}


void		RFCClient::setSocket(Socket &socket) {
	_socket = socket;
}

void		RFCClient::getData(Socket &socket) {
	recvCmd(socket);

}

RFCClient::~RFCClient() {}

void	RFCClient::sendHandshate(unsigned int idClient) // 6bytes
{
	if (_socket->connected() == true) {
		_socket->out().write("1000", 4);
		_socket->out().write((char *)&idClient, sizeof(short int));
	}
}

void	RFCClient::sendMove(const sf::Vector2f &pos, const sf::Vector2f &direction) // 9bytes
{
	if (_socket->connected() == true) {
		char c = RFCClient::SENDMOVE;
		_socket->out().write(&c,1);
		_socket->out().write((char *)&(pos.x), sizeof(short int));
		_socket->out().write((char *)&(pos.y), sizeof(short int));
		_socket->out().write((char *)&(direction.x), sizeof(short int));
		_socket->out().write((char *)&(direction.y), sizeof(short int));
	}
}

void	RFCClient::sendShoot(RFCClient::Weapon weapon, unsigned int idAmmo, const sf::Vector2f &pos, const sf::Vector2f &direction) // 12bytes
{
	if (_socket->connected() == true) {
		char c = RFCClient::SENDSHOOT;
		_socket->out().write(&c, 1);
		c = weapon;
		_socket->out().write(&c, 1);
		_socket->out().write((char *)&(idAmmo), sizeof(short int));
		_socket->out().write((char *)&(pos.x), sizeof(short int));
		_socket->out().write((char *)&(pos.y), sizeof(short int));
		_socket->out().write((char *)&(direction.x), sizeof(short int));
		_socket->out().write((char *)&(direction.y), sizeof(short int));
	}
}

void	RFCClient::sendCollision(unsigned int idClient, unsigned int idMonster, const sf::Vector2f &pos) // 9bytes
{
	if (_socket->connected() == true) {
		char c = RFCClient::SENDCOLLISION;
		_socket->out().write(&c, 1);
		_socket->out().write((char *)&(idClient), sizeof(short int));
		_socket->out().write((char *)&(idMonster), sizeof(short int));
		_socket->out().write((char *)&(pos.x), sizeof(short int));
		_socket->out().write((char *)&(pos.y), sizeof(short int));
	}
}

void	RFCClient::sendHitMonster(unsigned int idMonster, const sf::Vector2f &posMonster) // 7bytes
{
	if (_socket->connected() == true) {
		char c = RFCClient::SENDHITMONSTER;
		_socket->out().write(&c, 1);
		_socket->out().write((char *)&(idMonster), sizeof(short int));
		_socket->out().write((char *)&(posMonster.x), sizeof(short int));
		_socket->out().write((char *)&(posMonster.y), sizeof(short int));
	}
}

void	RFCClient::sendKillMonster(unsigned int idMonster, const sf::Vector2f &posMonster) // 7btytes
{
	if (_socket->connected() == true) {
		char c = RFCClient::SENDKILLMONSTER;
		_socket->out().write(&c, 1);
		_socket->out().write((char *)&(idMonster), sizeof(short int));
		_socket->out().write((char *)&(posMonster.x), sizeof(short int));
		_socket->out().write((char *)&(posMonster.y), sizeof(short int));
	}
}

void	RFCClient::recvCmd(Socket &socket) {
	char cmd;
	socket->in().get(&cmd, 1);
	switch (cmd)
	{
	case RECVMOVE:
		recvMove(socket);
		break;
	case RECVSHOOT:
		recvShoot(socket);
		break;
	case RECVCOLLISION:
		recvCollision(socket);
		break;
	case RECVHITMONSTER:
		recvHitMonster(socket);
		break;
	case RECVKILLMONSTER:
		recvKillMonster(socket);
		break;
	case RECVHANDSHAKE:
		recvKillMonster(socket);
		break;
	case RECVMONSTERSPAWN:
		recvMonsterSpawn(socket);
		break;
	case RECVMONSTERMOVE:
		recvMonsterMove(socket);
		break;
	case RECVMONSTERDESTROY:
		recvMonsterDestroy(socket);
		break;
	case RECVMONSTERFIRE:
		recvMonsterFire(socket);
		break;
	case RECVMONSTERKILLPLAYER:
		recvMonsterKillPlayer(socket);
		break;
	case RECVSTARTGAME:
		recvStartGame(socket);
		break;
	case RECVCLIENTCRASH:
		recvClientCrash(socket);
		break;
	default:
		break;
	}
}

void	RFCClient::recvHandshate(Socket &socket) {
	char buff[3];
	socket->in().get(buff, 3);
	if (strlen(buff) != 3)
		return;
	_isConnect = *(bool*)(buff);
	_id[PLAYER1] = *(short int*)(buff + 1);
}
void	RFCClient::recvMove(Socket &socket) {
	char buff[10];
	short int idPlayer;
	short int x;
	short int y;
	short int dirX;
	short int dirY;
	
	socket->in().get(buff, 10);
	if (strlen(buff) != 10)
		return;
	idPlayer = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);
	dirX = *(short int*)(buff + 6);
	dirY = *(short int*)(buff + 8);
}
void	RFCClient::recvShoot(Socket &socket) {
	Weapon weapon;
	short int x;
	short int y;
	short int dirX;
	short int dirY;
	short int idMun;
	char buff[11];

	socket->in().get(buff, 11);
	if (strlen(buff) != 3)
		return;
	weapon = *(Weapon*)(buff);
	x = *(short int*)(buff + sizeof(Weapon));
	y = *(short int*)(buff + sizeof(Weapon) + 2);
	dirX = *(short int*)(buff + sizeof(Weapon) + 4);
	dirY = *(short int*)(buff + sizeof(Weapon) + 6);
	idMun = *(short int*)(buff + sizeof(Weapon) + 8);

}
void	RFCClient::recvCollision(Socket &socket) {
	short int x;
	short int y;
	short int idClient;
	short int idMonster;
	char buff[8];

	socket->in().get(buff, 8);
	if (strlen(buff) != 3)
		return;
	idClient = *(short int*)(buff);
	idMonster = *(short int*)(buff + 2);
	x = *(short int*)(buff + 4);
	y = *(short int*)(buff + 6);

}
void	RFCClient::recvHitMonster(Socket &socket) {
	short int x;
	short int y;
	short int idMonster;
	char buff[6];
	
	socket->in().get(buff, 6);
	if (strlen(buff) != 6)
		return;
	idMonster = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);

}
void	RFCClient::recvKillMonster(Socket &socket) {
	short int x;
	short int y;
	short int idMonster;
	char buff[6];

	socket->in().get(buff, 6);
	if (strlen(buff) != 6)
		return;
	idMonster = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);
}

void	RFCClient::recvStartGame(Socket &socket) {
	char buff[6];

	socket->in().get(buff, 6);
	if (strlen(buff) != 6)
		return;
	_id[PLAYER2] = *(short int*)(buff);
	_id[PLAYER3] = *(short int*)(buff + 2);
	_id[PLAYER4] = *(short int*)(buff + 4);
}

void RFCClient::recvClientCrash(Socket &socket) {
	char buff[2];

	socket->in().get(buff, 2);
	if (strlen(buff) != 2)
		return;
	_idClientCrash = *(short int*)(buff);
}

void	RFCClient::recvMonsterSpawn(Socket &socket) {
	short int x;
	short int y;
	short int idMonster;
	Monster monster;
	char buff[6];

	socket->in().get(buff, 6);
	if (strlen(buff) != 6)
		return;
	monster = *(Monster*)(buff);
	idMonster = *(short int*)(buff + sizeof(Monster));
	x = *(short int*)(buff + sizeof(Monster) + 2);
	y = *(short int*)(buff + sizeof(Monster) + 4);
}

void	RFCClient::recvMonsterMove(Socket &socket) {
	short int x;
	short int y;
	short int dirX;
	short int dirY;
	short int or;
	short int idMonster;
	char buff[12];

	socket->in().get(buff, 12);
	if (strlen(buff) != 12)
		return;
	idMonster = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);
	dirX = *(short int*)(buff + 6);
	dirY = *(short int*)(buff + 8);
	or = *(short int*)(buff + 10);
}

void	RFCClient::recvMonsterDestroy(Socket &socket) {
	short int x;
	short int y;
	short int idMonster;
	char buff[6];

	_socket->in().get(buff, 6);
	if (strlen(buff) != 6)
		return;
	idMonster = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);
}

void	RFCClient::recvMonsterKillPlayer(Socket &socket) {
	short int x;
	short int y;
	short int idClient;
	char buff[6];

	_socket->in().get(buff, 6);
	if (strlen(buff) != 6)
		return;
	idClient = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);
}

void	RFCClient::recvMonsterFire(Socket &socket) {
	Weapon weapon;
	short int x;
	short int y;
	short int dirX;
	short int dirY;
	short int idMonster;
	char buff[11];

	_socket->in().get(buff, 11);
	if (strlen(buff) != 11)
		return;
	weapon = *(Weapon*)(buff);
	idMonster = *(short int*)(buff + sizeof(Weapon) + 1);
	x = *(short int*)(buff + sizeof(Weapon) + 3);
	y = *(short int*)(buff + sizeof(Weapon) + 5);
	dirX = *(short int*)(buff + sizeof(Weapon) + 7);
	dirY = *(short int*)(buff + sizeof(Weapon) + 9);
}