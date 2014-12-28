# include <cstring>
#include "RFCClient.h"
#include "BasicType.h"

RFCClient::RFCClient(Network::Socket &socket, GameSpecificFactory &factory, World &world) : _factory(factory), _world(world) {
	_socket = &socket;
	_socket->onRecive(::hpl::bind(&RFCClient::recvCmd, this, ::hpl::Placeholder::_1));
	_handshate = false;
	_isConnect = false;
	_id[PLAYER1] = 0;
	_id[PLAYER2] = 0;
	_id[PLAYER3] = 0;
	_id[PLAYER4] = 0;
}

//void		RFCClient::setSocket(Socket &socket) {
//	_socket = socket;
//}
//
//void		RFCClient::getData(Socket &socket) {
//	recvCmd(socket);
//
//}

RFCClient::~RFCClient() {}

void	RFCClient::sendHandshake(unsigned int idClient) // 6bytes
{
	if (_socket->connected() == true) {
		_socket->out().write("1000", 4);
		usint tmp = (short int)(idClient);
		_socket->out().write((char *)&tmp, sizeof(short int));
	}
}

void	RFCClient::sendMove(const sf::Vector2f &pos, const sf::Vector2f &direction) // 9bytes
{
	if (_socket->connected() == true) {
		char c = RFCClient::SENDMOVE;
		_socket->out().write(&c,1);
		usint tmp = (short int)(pos.x);
		_socket->out().write((char *)&tmp, sizeof(short int));
		tmp = (short int)(pos.y);
		_socket->out().write((char *)&tmp, sizeof(short int));
		tmp = (short int)(direction.x);
		_socket->out().write((char *)&tmp, sizeof(short int));
		tmp = (short int)(direction.y);
		_socket->out().write((char *)&tmp, sizeof(short int));
	}
}

void	RFCClient::sendShoot(RFCClient::Weapon weapon, unsigned int idAmmo, const sf::Vector2f &pos, const sf::Vector2f &direction) // 12bytes
{
	if (_socket->connected() == true) {
		char c = RFCClient::SENDSHOOT;
		_socket->out().write(&c, 1);
		c = weapon;
		_socket->out().write(&c, 1);
		usint tmp = (short int)(idAmmo);
		_socket->out().write((char *)&tmp, sizeof(short int));
		tmp = (short int)(pos.x);
		_socket->out().write((char *)&tmp, sizeof(short int));
		tmp = (short int)(pos.y);
		_socket->out().write((char *)&tmp, sizeof(short int));
		tmp = (short int)(direction.x);
		_socket->out().write((char *)&tmp, sizeof(short int));
		tmp = (short int)(direction.y);
		_socket->out().write((char *)&tmp, sizeof(short int));
	}
}

void	RFCClient::sendCollision(unsigned int idClient, unsigned int idMonster, const sf::Vector2f &pos) // 9bytes
{
	if (_socket->connected() == true) {
		char c = RFCClient::SENDCOLLISION;
		_socket->out().write(&c, 1);
		usint tmp = (short int)(idClient);
		_socket->out().write((char *)&tmp, sizeof(short int));
		tmp = (short int)(idMonster);
		_socket->out().write((char *)&tmp, sizeof(short int));
		tmp = (short int)(pos.x);
		_socket->out().write((char *)&tmp, sizeof(short int));
		tmp = (short int)(pos.y);
		_socket->out().write((char *)&tmp, sizeof(short int));
	}
}

void	RFCClient::sendHitMonster(unsigned int idMonster, const sf::Vector2f &posMonster) // 7bytes
{
	if (_socket->connected() == true) {
		char c = RFCClient::SENDHITMONSTER;
		_socket->out().write(&c, 1);
		usint tmp = (short int)(idMonster);
		_socket->out().write((char *)&tmp, sizeof(short int));
		tmp = (short int)(posMonster.x);
		_socket->out().write((char *)&tmp, sizeof(short int));
		tmp = (short int)(posMonster.y);
		_socket->out().write((char *)&tmp, sizeof(short int));
	}
}

void	RFCClient::sendKillMonster(unsigned int idMonster, const sf::Vector2f &posMonster) // 7btytes
{
	if (_socket->connected() == true) {
		char c = RFCClient::SENDKILLMONSTER;
		_socket->out().write(&c, 1);
		usint tmp = (short int)(idMonster);
		_socket->out().write((char *)&tmp, sizeof(short int));
		tmp = (short int)(posMonster.x);
		_socket->out().write((char *)&tmp, sizeof(short int));
		tmp = (short int)(posMonster.y);
		_socket->out().write((char *)&tmp, sizeof(short int));
	}
}
#include <iostream>
void	RFCClient::recvCmd(Network::Socket &socket) {
	std::cout << "get" << std::endl;

	char cmd;
	_socket->in().get(&cmd, 1);
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
	case RECVMUNITIONS:
		recvMunitions();
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

void	RFCClient::recvHandshake() {
	char buff[3];
	int nb = _socket->in().get(buff, 3);
	if (nb != 3)
		return;
	_isConnect = *(bool*)(buff);
	_id[PLAYER1] = *(short int*)(buff + 1);
}

void	RFCClient::recvMunitions() {
	char buff[2];
	short int nbMunitions;
	int nb = _socket->in().get(buff, 2);
	if (nb != 2)
		return;
	nbMunitions = *(short int*)(buff);
}

void	RFCClient::recvMove() {
	char buff[10];
	short int idPlayer;
	short int x;
	short int y;
	short int dirX;
	short int dirY;
	
	int nb = _socket->in().get(buff, 10);
	if (nb != 10)
		return;
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
	char buff[11];

	int nb = _socket->in().get(buff, 11);
	if (nb != 11)
		return;
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

	int nb = _socket->in().get(buff, 8);
	if (nb != 8)
		return;
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
	
	int nb = _socket->in().get(buff, 6);
	if (nb != 6)
		return;
	idMonster = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);

}
void	RFCClient::recvKillMonster() {
	short int x;
	short int y;
	short int idMonster;
	char buff[6];

	int nb = _socket->in().get(buff, 6);
	if (nb != 6)
		return;
	idMonster = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);
}

void	RFCClient::recvStartGame() {
	char buff[6];

	int nb = _socket->in().get(buff, 6);
	if (strlen(buff) != 6)
		return;
	_id[PLAYER2] = *(short int*)(buff);
	_id[PLAYER3] = *(short int*)(buff + 2);
	_id[PLAYER4] = *(short int*)(buff + 4);
}

void RFCClient::recvClientCrash() {
	char buff[2];

	int nb = _socket->in().get(buff, 2);
	if (nb != 2)
		return;
	_idClientCrash = *(short int*)(buff);
}

void	RFCClient::recvMonsterSpawn() {
	short int x;
	short int y;
	short int idMonster;
	Monster monster;
	char buff[6];

	int nb = _socket->in().get(buff, 6);
	if (nb != 6)
		return;
	monster = *(Monster*)(buff);
	idMonster = *(short int*)(buff + sizeof(Monster));
	x = *(short int*)(buff + sizeof(Monster) + 2);
	y = *(short int*)(buff + sizeof(Monster) + 4);


	// Create monster in the world

	unsigned int id[1];	

	_factory.createTestEnemy(id, _world);
	_rfcToWorldId[idMonster] = id[0];
	_worldToRfcId[id[0]] = idMonster;
	_world.transformComponents[id[0]]->position = sf::Vector2f(x, y);
}

void	RFCClient::recvMonsterMove() {
	short int x;
	short int y;
	short int dirX;
	short int dirY;
	short int or;
	short int idMonster;
	char buff[12];

	int nb = _socket->in().get(buff, 12);
	if (nb != 12)
		return;
	idMonster = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);
	dirX = *(short int*)(buff + 6);
	dirY = *(short int*)(buff + 8);
	or = *(short int*)(buff + 10);

	// Move monster in the world && Spawn if it does not exist

	if (_rfcToWorldId.find(idMonster) == _rfcToWorldId.end())
	{
		unsigned int id[1];

		_factory.createTestEnemy(id, _world);
		_rfcToWorldId[idMonster] = id[0];
		_worldToRfcId[id[0]] = idMonster;
		_world.transformComponents[id[0]]->position = sf::Vector2f(x, y);
		_world.transformComponents[id[0]]->rotation = or;
	}
	_world.movementComponents[_rfcToWorldId[idMonster]]->direction = sf::Vector2f(dirX, dirY);
}

void	RFCClient::recvMonsterDestroy() {
	short int x;
	short int y;
	short int idMonster;
	char buff[6];

	int nb = _socket->in().get(buff, 6);
	if (nb != 6)
		return;
	idMonster = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);

	// Destroy monster in the world

	_world.infoComponents[_rfcToWorldId[idMonster]]->dead = true;

	_worldToRfcId.erase(_worldToRfcId.find(_rfcToWorldId.find(idMonster)->second));
	_rfcToWorldId.erase(_rfcToWorldId.find(idMonster));
}

void	RFCClient::recvMonsterKillPlayer() {
	short int x;
	short int y;
	short int idClient;
	char buff[6];

	int nb = _socket->in().get(buff, 6);
	if (nb != 6)
		return;
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

	int nb = _socket->in().get(buff, 11);
	if (nb != 11)
		return;
	weapon = *(Weapon*)(buff);
	idMonster = *(short int*)(buff + sizeof(Weapon) + 1);
	x = *(short int*)(buff + sizeof(Weapon) + 3);
	y = *(short int*)(buff + sizeof(Weapon) + 5);
	dirX = *(short int*)(buff + sizeof(Weapon) + 7);
	dirY = *(short int*)(buff + sizeof(Weapon) + 9);
}