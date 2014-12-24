#include "RFCClient.h"

RFCClient::RFCClient() {
	_handshate = false;
	_isConnect = false;
	_id[PLAYER1] = 0;
	_id[PLAYER2] = 0;
	_id[PLAYER3] = 0;
	_id[PLAYER4] = 0;
}

RFCClient::~RFCClient() {}

void	RFCClient::sendHandshate(unsigned int idClient) // 6bytes
{
	if (_socket->isConnect() == true) {
		_socket->out().write("1000", 4);
		_socket->out().write((char *)&idClient, sizeof(short int));
	}
}

void	RFCClient::sendMove(const sf::Vector2f &pos, const sf::Vector2f &direction) // 9bytes
{
	if (_socket->isConnect() == true) {
		_socket->out().write(RFCClient::SENDMOVE,1);
		_socket->out().write((char *)&(pos.x), sizeof(short int));
		_socket->out().write((char *)&(pos.y), sizeof(short int));
		_socket->out().write((char *)&(direction.x), sizeof(short int));
		_socket->out().write((char *)&(direction.y), sizeof(short int));
	}
}

void	RFCClient::sendShoot(RFCClient::Weapon weapon, unsigned int idAmmo, const sf::Vector2f &pos, const sf::Vector2f &direction) // 12bytes
{
	if (_socket->isConnect() == true) {
		_socket->out().write(RFCClient::SENDSHOOT, 1);
		_socket->out().write(&weapon, 1);
		_socket->out().write((char *)&(idAmmo), sizeof(short int));
		_socket->out().write((char *)&(pos.x), sizeof(short int));
		_socket->out().write((char *)&(pos.y), sizeof(short int));
		_socket->out().write((char *)&(direction.x), sizeof(short int));
		_socket->out().write((char *)&(direction.y), sizeof(short int));
	}
}

void	RFCClient::sendCollision(unsigned int idClient, unsigned int idMonster, const sf::Vector2f &pos) // 9bytes
{
	if (_socket->isConnect() == true) {
		_socket->out().write(RFCClient::SENDCOLLISION, 1);
		_socket->out().write((char *)&(idClient), sizeof(short int));
		_socket->out().write((char *)&(idMonster), sizeof(short int));
		_socket->out().write((char *)&(pos.x), sizeof(short int));
		_socket->out().write((char *)&(pos.y), sizeof(short int));
	}
}

void	RFCClient::sendHitMonster(unsigned int idMonster, const sf::Vector2f &posMonster) // 7bytes
{
	if (_socket->isConnect() == true) {
		_socket->out().write(RFCClient::SENDHITMONSTER, 1);
		_socket->out().write((char *)&(idMonster), sizeof(short int));
		_socket->out().write((char *)&(posMonster.x), sizeof(short int));
		_socket->out().write((char *)&(posMonster.y), sizeof(short int));
	}
}

void	RFCClient::sendKillMonster(unsigned int idMonster, const sf::Vector2f &posMonster) // 7btytes
{
	if (_socket->isConnect() == true) {
		_socket->out().write(RFCClient::SENDKILLMONSTER, 1);
		_socket->out().write((char *)&(idMonster), sizeof(short int));
		_socket->out().write((char *)&(posMonster.x), sizeof(short int));
		_socket->out().write((char *)&(posMonster.y), sizeof(short int));
	}
}

void	RFCClient::recvCmd() {
	char cmd;
	_socket->in().get(cmd, 1);
	switch (cmd)
	{
	case RECVMOVE:
		recvMove();
		break;
	case RECVSHOOT:
		recvShoot();
		break;
	case RECVCOLLISION:
		recvCollision();
		break;
	case RECVHITMONSTER:
		recvHitMonster();
		break;
	case RECVKILLMONSTER:
		recvKillMonster();
		break;
	case RECVHANDSHAKE:
		recvKillMonster();
		break;
	case RECVMONSTERSPAWN:
		recvMonsterSpawn();
		break;
	case RECVMONSTERMOVE:
		recvMonsterMove();
		break;
	case RECVMONSTERDESTROY:
		recvMonsterDestroy();
		break;
	case RECVMONSTERFIRE:
		recvMonsterFire();
		break;
	case RECVMONSTERKILLPLAYER:
		recvMonsterKillPlayer();
		break;
	case RECVSTARTGAME:
		recvStartGame();
		break;
	case RECVCLIENTCRASH:
		recvClientCrash();
		break;
	default:
		break;
	}
}

void	RFCClient::recvHandshate() {
	char buff[3];
	_socket->in().get(buff, 3);
	_isConnect = *(bool*)(buff);
	_id[PLAYER1] = *(short int*)(buff + 1);
}
void	RFCClient::recvMove() {
	char buff[10];
	short int idPlayer;
	short int x;
	short int y;
	short int dirX;
	short int dirY;
	
	_socket->in().get(buff, 10);
	idPlayer = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);
	dirX = *(short int*)(buff + 6);
	dirY = *(short int*)(buff + 8);
}
void	RFCClient::recvShoot() {
	Weapon weapon;
	short int x;
	short int y;
	short int dirX;
	short int dirY;
	short int idMun;
	char buff[10];

	_socket->in().get(buff, 11);
	weapon = *(Weapon*)(buff);
	x = *(short int*)(buff + sizeof(Weapon));
	y = *(short int*)(buff + sizeof(Weapon) + 2);
	dirX = *(short int*)(buff + sizeof(Weapon) + 4);
	dirY = *(short int*)(buff + sizeof(Weapon) + 6);
	idMun = *(short int*)(buff + sizeof(Weapon) + 8);

}
void	RFCClient::recvCollision() {
	short int x;
	short int y;
	short int idClient;
	short int idMonster;
	char buff[8];

	_socket->in().get(buff, 8);
	idClient = *(short int*)(buff);
	idMonster = *(short int*)(buff + 2);
	x = *(short int*)(buff + 4);
	y = *(short int*)(buff + 6);

}
void	RFCClient::recvHitMonster() {
	short int x;
	short int y;
	short int idMonster;

	char buff[6];
	_socket->in().get(buff, 6);
	idMonster = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);

}
void	RFCClient::recvKillMonster() {
	short int x;
	short int y;
	short int idMonster;

	char buff[6];
	_socket->in().get(buff, 6);
	idMonster = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);
}

void	RFCClient::recvStartGame() {
	char buff[6];
	_socket->in().get(buff, 6);
	_id[PLAYER2] = *(short int*)(buff);
	_id[PLAYER3] = *(short int*)(buff + 2);
	_id[PLAYER4] = *(short int*)(buff + 4);
}

void RFCClient::recvClientCrash() {
	char buff[2];
	_socket->in().get(buff, 2);
	_idClientCrash = *(short int*)(buff);
}

void	RFCClient::recvMonsterSpawn() {
	short int x;
	short int y;
	short int idMonster;
	Monster monster;

	char buff[6];
	_socket->in().get(buff, 6);
	monster = *(Monster*)(buff);
	idMonster = *(short int*)(buff + sizeof(Monster));
	x = *(short int*)(buff + sizeof(Monster) + 2);
	y = *(short int*)(buff + sizeof(Monster) + 4);
}

void	RFCClient::recvMonsterMove() {
	short int x;
	short int y;
	short int dirX;
	short int dirY;
	short int or;
	short int idMonster;
	char buff[12];

	_socket->in().get(buff, 12);
	idMonster = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);
	dirX = *(short int*)(buff + 6);
	dirY = *(short int*)(buff + 8);
	or = *(short int*)(buff + 10);
}

void	RFCClient::recvMonsterDestroy() {
	short int x;
	short int y;
	short int idMonster;
	char buff[6];

	_socket->in().get(buff, 6);
	idMonster = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);
}

void	RFCClient::recvMonsterKillPlayer() {
	short int x;
	short int y;
	short int idClient;
	char buff[6];

	_socket->in().get(buff, 6);
	idClient = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);
}

void	RFCClient::recvMonsterFire() {
	Weapon weapon;
	short int x;
	short int y;
	short int dirX;
	short int dirY;
	short int idMonster;
	char buff[11];

	_socket->in().get(buff, 11);
	weapon = *(Weapon*)(buff);
	idMonster = *(short int*)(buff + sizeof(Weapon) + 1);
	x = *(short int*)(buff + sizeof(Weapon) + 3);
	y = *(short int*)(buff + sizeof(Weapon) + 5);
	dirX = *(short int*)(buff + sizeof(Weapon) + 7);
	dirY = *(short int*)(buff + sizeof(Weapon) + 9);
}