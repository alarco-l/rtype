# include <cstring>
#include "RFCClient.h"
#include "BasicType.h"

RFCClient::RFCClient(Network::Socket &socket, GameSpecificFactory &factory, World &world, Game *game) : _factory(factory), _world(world), _game(game) {
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

void	RFCClient::recvCmd(Network::Socket &socket) {
	while (socket.in().size())
	{
		char	c;
		socket.in().get(&c, 1);
		RecvCommand	cmd = (RecvCommand)c;

		switch (cmd)
		{
		case RECVMOVE:
			if (socket.in().size() >= 10)
			{
				char	buff[10];
				socket.in().get(buff, sizeof(buff));
				recvMove(buff);
			}
			else
				return;
		case RECVSHOOT:
			if (socket.in().size() >= 11)
			{
				char	buff[11];
				socket.in().get(buff, sizeof(buff));
				recvShoot(buff);
			}
			else
				return;
			break;
		case RECVCOLLISION:
			if (socket.in().size() >= 8)
			{
				char	buff[8];
				socket.in().get(buff, sizeof(buff));
				recvCollision(buff);
			}
			else
				return;
			break;
		case RECVHITMONSTER:
			if (socket.in().size() >= 6)
			{
				char	buff[6];
				socket.in().get(buff, sizeof(buff));
				recvHitMonster(buff);
			}
			else
				return;
			break;
		case RECVKILLMONSTER:
			if (socket.in().size() >= 6)
			{
				char	buff[6];
				socket.in().get(buff, sizeof(buff));
				recvKillMonster(buff);
			}
			else
				return;
			break;
		case RECVHANDSHAKE:
			if (socket.in().size() >= 6)
			{
				char	buff[6];
				socket.in().get(buff, sizeof(buff));
				recvHandshake(buff);
			}
			else
				return;
			break;
		case RECVMONSTERSPAWN:
			if (socket.in().size() >= 7)
			{
				char	buff[7];
				socket.in().get(buff, sizeof(buff));
				recvMonsterSpawn(buff);
			}
			else
				return;
			break;
		case RECVMONSTERMOVE:
			if (socket.in().size() >= sizeof(float) * 5 + 2)
			{
				char	buff[sizeof(float) * 5 + 2];
				socket.in().get(buff, sizeof(buff));
				recvMonsterMove(buff);
			}
			else
				return;
			break;
		case RECVMONSTERDESTROY:
			if (socket.in().size() >= 11)
			{
				char	buff[11];
				socket.in().get(buff, sizeof(buff));
				recvMonsterDestroy(buff);
			}
			else
				return;
			break;
		case RECVMONSTERFIRE:
			if (socket.in().size() >= sizeof(float) * 4 + 3)
			{
				char	buff[sizeof(float) * 4 + 3];
				socket.in().get(buff, sizeof(buff));
				recvMonsterFire(buff);
			}
			else
				return;
			break;
		case RECVMONSTERKILLPLAYER:
			if (socket.in().size() >= 6)
			{
				char	buff[6];
				socket.in().get(buff, sizeof(buff));
				recvMonsterKillPlayer(buff);
			}
			else
				return;
			break;
		case RECVMUNITIONS:
			if (socket.in().size() >= 2)
			{
				char	buff[2];
				socket.in().get(buff, sizeof(buff));
				recvMunitions(buff);
			}
			else
				return;
			break;
		case RECVSTARTGAME:
			if (socket.in().size() >= 10)
			{
				char	buff[10];
				socket.in().get(buff, sizeof(buff));
				recvStartGame(buff);
			}
			else
				return;
			break;
		case RECVCLIENTCRASH:
			if (socket.in().size() >= 2)
			{
				char	buff[2];
				socket.in().get(buff, sizeof(buff));
				recvClientCrash(buff);
			}
			else
				return;
			break;
		default:
			break;
		}
	}
}

void	RFCClient::recvHandshake(const char *buff) {

	_isConnect = *(bool*)(buff);
	_id[PLAYER1] = *(short int*)(buff + 1);
}

void	RFCClient::recvMunitions(const char *buff) {
	short int nbMunitions;

	nbMunitions = *(short int*)(buff);
}

void	RFCClient::recvMove(const char *buff) {
	short int x;
	short int y;
	short int dirX;
	short int dirY;
	short int idClient;

	idClient = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);
	dirX = *(short int*)(buff + 6);
	dirY = *(short int*)(buff + 8);

	// MOVE OTHER PLAYER

	_world.movementComponents[_rfcToWorldId[idClient]]->direction = sf::Vector2f(dirX, dirY);
}
void	RFCClient::recvShoot(const char *buff) {
	Weapon weapon;
	short int x;
	short int y;
	short int dirX;
	short int dirY;
	short int idMun;

	weapon = *(Weapon*)(buff);
	x = *(short int*)(buff + sizeof(Weapon));
	y = *(short int*)(buff + sizeof(Weapon) + 2);
	dirX = *(short int*)(buff + sizeof(Weapon) + 4);
	dirY = *(short int*)(buff + sizeof(Weapon) + 6);
	idMun = *(short int*)(buff + sizeof(Weapon) + 8);

}
void	RFCClient::recvCollision(const char *buff) {
	short int x;
	short int y;
	short int idClient;
	short int idMonster;

	idClient = *(short int*)(buff);
	idMonster = *(short int*)(buff + 2);
	x = *(short int*)(buff + 4);
	y = *(short int*)(buff + 6);
}
void	RFCClient::recvHitMonster(const char *buff) {
	short int x;
	short int y;
	short int idMonster;
	
	idMonster = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);

}
void	RFCClient::recvKillMonster(const char *buff) {
	short int x;
	short int y;
	short int idMonster;

	idMonster = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);
}

void	RFCClient::recvStartGame(const char *buff) {
	_id[PLAYER2] = *(short int*)(buff);
	_id[PLAYER3] = *(short int*)(buff + 2);
	_id[PLAYER4] = *(short int*)(buff + 4);

	// Create 3 other players

	unsigned int player2[RType::Player::MAX];

	_factory.createPlayer(player2, _world);
	_rfcToWorldId[player2[RType::Player::SHIP]] = _id[PLAYER2];
	_worldToRfcId[_id[PLAYER2]] = player2[RType::Player::SHIP];

	_world.renderComponents[player2[RType::Player::SHIP]]->color = sf::Color(0, 255, 0);
	_world.transformComponents[player2[RType::Player::SHIP]]->position = sf::Vector2f(0.0f, 250.0f);

	unsigned int player3[RType::Player::MAX];

	_factory.createPlayer(player3, _world);
	_rfcToWorldId[player3[RType::Player::SHIP]] = _id[PLAYER3];
	_worldToRfcId[_id[PLAYER3]] = player3[RType::Player::SHIP];

	_world.renderComponents[player3[RType::Player::SHIP]]->color = sf::Color(255, 0, 0);
	_world.transformComponents[player3[RType::Player::SHIP]]->position = sf::Vector2f(0.0f, 500.0f);

	unsigned int player4[RType::Player::MAX];

	_factory.createPlayer(player4, _world);
	_rfcToWorldId[player4[RType::Player::SHIP]] = _id[PLAYER4];
	_worldToRfcId[_id[PLAYER4]] = player4[RType::Player::SHIP];

	_world.renderComponents[player4[RType::Player::SHIP]]->color = sf::Color(255, 255, 0);
	_world.transformComponents[player4[RType::Player::SHIP]]->position = sf::Vector2f(0.0f, 750.0f);
}

void RFCClient::recvClientCrash(const char *buff) {
	_idClientCrash = *(short int*)(buff);
}

void	RFCClient::recvMonsterSpawn(const char *buff) {
	short int x;
	short int y;
	short int idMonster;
	Monster monster;

	monster = *(Monster*)(buff);
	idMonster = *(short int*)(buff + sizeof(Monster));
	x = *(short int*)(buff + sizeof(Monster) + 2);
	y = *(short int*)(buff + sizeof(Monster) + 4);


	// Create monster in the world

	//unsigned int id[1];	

	//_factory.createTestEnemy(id, _world);
	//_rfcToWorldId[idMonster] = id[0];
	//_worldToRfcId[id[0]] = idMonster;
	//_world.transformComponents[id[0]]->position = sf::Vector2f(x, y);
}

void	RFCClient::recvMonsterMove(const char *buff) {
	float x;
	float y;
	float dirX;
	float dirY;
	float or;
	unsigned short idMonster;

	idMonster = *(unsigned short*)(buff);
	x = *(float*)(buff + sizeof(unsigned short));
	y = *(float*)(buff + sizeof(unsigned short) + sizeof(float));
	dirX = *(float*)(buff + sizeof(unsigned short) + sizeof(float) * 2);
	dirY = *(float*)(buff + sizeof(unsigned short) + sizeof(float) * 3);
	or = *(float*)(buff + sizeof(unsigned short) + sizeof(float) * 4);

	static int nb = 0;

	std::cout << "PASSE " << nb++ << std::endl;

	 //Move monster in the world && Spawn if it does not exist
	if (_rfcToWorldId.find(idMonster) == _rfcToWorldId.end())
	{
		unsigned int id[1];
		_factory.createTestEnemy(id, _world);
		_rfcToWorldId[idMonster] = id[0];
		_worldToRfcId[id[0]] = idMonster;
		_world.transformComponents[id[0]]->position = sf::Vector2f(x, y);
		_world.transformComponents[id[0]]->rotation = or;
	}

	if (_world.movementComponents.size() > _rfcToWorldId[idMonster] && _world.movementComponents[_rfcToWorldId[idMonster]] != NULL)
		_world.movementComponents[_rfcToWorldId[idMonster]]->direction = sf::Vector2f(dirX, dirY);
}

void	RFCClient::recvMonsterDestroy(const char *buff) {
	short int x;
	short int y;
	short int idMonster;

	idMonster = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);

	// Destroy monster in the world

	//_world.infoComponents[_rfcToWorldId[idMonster]]->dead = true;

	//_worldToRfcId.erase(_worldToRfcId.find(_rfcToWorldId.find(idMonster)->second));
	//_rfcToWorldId.erase(_rfcToWorldId.find(idMonster));
}

void	RFCClient::recvMonsterKillPlayer(const char *buff) {
	short int x;
	short int y;
	short int idClient;

	idClient = *(short int*)(buff);
	x = *(short int*)(buff + 2);
	y = *(short int*)(buff + 4);
}

void	RFCClient::recvMonsterFire(const char *buff) {
	Weapon weapon;
	float x;
	float y;
	float dirX;
	float dirY;
	short int idMonster;

	weapon = (Weapon)(*buff);
	idMonster = *(short int*)(buff + 1);
	x = *(float*)(buff + 3);
	y = *(float*)(buff + sizeof(float) + 3);
	dirX = *(float*)(buff + sizeof(float) * 2 + 3);
	dirY = *(float*)(buff + sizeof(float) * 3 + 3);

	//if (_rfcToWorldId.find(idMonster) != _rfcToWorldId.end() && _world.weaponComponents[_rfcToWorldId[idMonster]] != NULL)
	//{
	//	unsigned int id[1];
	//	_factory.createMissileProjectile(id, _rfcToWorldId[idMonster], _world, _game->getScreenSize());
	//	_rfcToWorldId[idMonster] = id[0];
	//	_worldToRfcId[id[0]] = idMonster;
	//	_world.transformComponents[id[0]]->position = sf::Vector2f(x, y);
	//	_world.transformComponents[id[0]]->rotation = 180.0f;

	//	if (_world.movementComponents.size() > _rfcToWorldId[idMonster] && _world.movementComponents[_rfcToWorldId[idMonster]] != NULL)
	//		_world.movementComponents[_rfcToWorldId[idMonster]]->direction = sf::Vector2f(dirX, dirY);
	//}
}