#include "RFC.h"

RFC::RFC(Network::Socket &socket) : _hasHandshake(false), _socket(&socket)
{
	_socket->onRecive(::hpl::bind(&RFC::recvCmd, this, ::hpl::Placeholder::_1));
}
RFC::~RFC() {}

void				RFC::recvCmd(Network::Socket &socket) {
	//static int i = 0;
	//std::fstream tata("tata.txt", std::fstream::in | std::fstream::app);
	while (socket.in().size())
	{
		char	c;
		socket.in().get(&c, 1);
		RFC::RecvCommand cmd = (RFC::RecvCommand)c;

		switch (cmd)
		{
		case RFC::RECVHANDSHAKE:
			break;
		case RFC::RECVMOVE:
			if (socket.in().size() >= 8)
			{
				RFC::Move mov;
				char	buff[8];
				socket.in().get(buff, sizeof(buff));
				mov.coord.posX = *(short int*)buff;
				mov.coord.posY = *(short int*)(buff + 2);
				mov.dir.dirX = *(short int*)(buff + 4);
				mov.dir.dirY = *(short int*)(buff + 6);
				if (_onMoveEvent)
					_onMoveEvent(*this, mov);
			}
			else
				return;
			break;
		case RFC::RECVSHOOT:
			if (socket.in().size() >= 10)
			{
				RFC::Shoot shoot;
				char	buff[10];
				socket.in().get(buff, sizeof(buff));
				shoot.idMuni = *(short int*)(buff);
				shoot.coord.posX = *(short int*)(buff + 2);
				shoot.coord.posY = *(short int*)(buff + 4);
				shoot.dir.dirX = *(short int*)(buff + 6);
				shoot.dir.dirY = *(short int*)(buff + 8);
				if (_onShootEvent)
					_onShootEvent(*this, shoot);
			}
			else
				return;
			break;
		case RFC::RECVCOLLISION:
			if (socket.in().size() >= 8)
			{
				RFC::Colision colision;
				char	buff[8];
				socket.in().get(buff, sizeof(buff));
				colision.idOnColision1 = *(short int*)(buff);
				colision.idOnColision2 = *(short int*)(buff + 2);
				colision.coord.posX = *(short int*)(buff + 4);
				colision.coord.posY = *(short int*)(buff + 6);
				if (_onColisionEvent)
					_onColisionEvent(*this, colision);
			}
			else
				return;
			break;
		case RFC::RECVHITMONSTER:
			if (socket.in().size() >= 6)
			{
				RFC::HitMonster hitMonster;
				char	buff[6];
				socket.in().get(buff, sizeof(buff));
				hitMonster.idMonster = *(short int*)(buff);
				hitMonster.coord.posX = *(short int*)(buff + 2);
				hitMonster.coord.posY = *(short int*)(buff + 4);
				if (_onHitEvent)
					_onHitEvent(*this, hitMonster);
			}
			else
				return;
			break;
		case RFC::RECVKILLMONSTER:
			if (socket.in().size() >= 6)
			{
				RFC::HitMonster killMonster;
				char	buff[6];
				socket.in().get(buff, sizeof(buff));
				killMonster.idMonster = *(short int*)(buff);
				killMonster.coord.posX = *(short int*)(buff + 2);
				killMonster.coord.posY = *(short int*)(buff + 4);
				socket.in().get(buff, 6);
				if (_onKillEvent)
					_onKillEvent(*this, killMonster);
			}
			else
				return;
			break;
		default:
			break;
		}
	}
}

void				RFC::sendStartGame(sint munition1, sint munition2) {
	char c = RFC::SENDSTARTGAME;
	_socket->out().write(&c, 1);

	usint tmp = (short int)(_idClient[0]);
	_socket->out().write((char *)&tmp, sizeof(short int));

	tmp = (short int)(_idClient[1]);
	_socket->out().write((char *)&tmp, sizeof(short int));

	tmp = (short int)(_idClient[2]);
	_socket->out().write((char *)&tmp, sizeof(short int));

	tmp = (short int)(_idClient[3]);
	_socket->out().write((char *)&tmp, sizeof(short int));

	tmp = (short int)(RFC::W1);
	_socket->out().write((char *)&tmp, sizeof(short int));

	tmp = (short int)(RFC::W2);
	_socket->out().write((char *)&tmp, sizeof(short int));
}
void				RFC::sendClientCrash(sint idClient) {
	char c = RFC::SENDSTARTGAME;
	_socket->out().write(&c, 1);

	usint tmp = (short int)(_idClient[0]);
	_socket->out().write((char *)&tmp, sizeof(short int));
}

void				RFC::sendMonsterSpawn(RFC::MonsterSpawn monster) {
	char c = RFC::SENDMONSTERSPAWN;
	_socket->out().write(&c, 1);

	c = monster.type;
	_socket->out().write(&c, 1);

	usint tmp = (short int)(monster.idMonster);
	_socket->out().write((char *)&tmp, sizeof(short int));

	tmp = (short int)(monster.coord.posX);
	_socket->out().write((char *)&tmp, sizeof(short int));

	tmp = (short int)(monster.coord.posY);
	_socket->out().write((char *)&tmp, sizeof(short int));

}

void				RFC::sendMonsterMove(RFC::MonsterMove move) { 
	char c = RFC::SENDMONSTERMOVE;
	_socket->out().write(&c, 1);
	
	usint tmp = (short int)(move.idMonster);
	_socket->out().write((char *)&tmp, sizeof(short int));
	_socket->out().write((char *)&move.coord.posX, sizeof(move.coord.posX));
	_socket->out().write((char *)&move.coord.posY, sizeof(move.coord.posY));
	_socket->out().write((char *)&move.dir.dirX, sizeof(move.dir.dirX));
	_socket->out().write((char *)&move.dir.dirY, sizeof(move.dir.dirY));
	_socket->out().write((char *)&move.orientation, sizeof(move.orientation));
}

void				RFC::sendMonsterDestroy(RFC::HitMonster hitMonster) {
	char c = RFC::SENDMONSTERDESTROY;
	_socket->out().write(&c, 1);

	usint tmp = (short int)(hitMonster.idMonster);
	_socket->out().write((char *)&tmp, sizeof(short int));
	tmp = (short int)(hitMonster.coord.posX);
	_socket->out().write((char *)&tmp, sizeof(short int));
	tmp = (short int)(hitMonster.coord.posY);
}

void				RFC::sendMonsterFire(RFC::MonsterShoot shoot) {
	char c = RFC::SENDMONSTERFIRE;
	_socket->out().write(&c, 1);

	c = shoot.weapon;
	_socket->out().write(&c, 1);

	usint tmp = (short int)(shoot.idMonster);
	_socket->out().write((char *)&tmp, sizeof(short int));
	_socket->out().write((char *)&shoot.coord.posX, sizeof(shoot.coord.posX));
	_socket->out().write((char *)&shoot.coord.posY, sizeof(shoot.coord.posY));
	_socket->out().write((char *)&shoot.dir.dirX, sizeof(shoot.dir.dirX));
	_socket->out().write((char *)&shoot.dir.dirY, sizeof(shoot.dir.dirY));
}
void				RFC::sendMonsterKillPlayer(RFC::MonsterKillPlayer kill) {
	char c = RFC::SENDMONSTERKILLPLAYER;
	_socket->out().write(&c, 1);

	usint tmp = (short int)(kill.idClient);
	_socket->out().write((char *)&tmp, sizeof(short int));
	tmp = (short int)(kill.coord.posX);
	_socket->out().write((char *)&tmp, sizeof(short int));
	tmp = (short int)(kill.coord.posY);
}

void				RFC::sendNewMunition(sint munition) {
	char c = RFC::SENDMUNITIONS;
	_socket->out().write(&c, 1);

	usint tmp = (short int)(munition);
	_socket->out().write((char *)&tmp, sizeof(short int));
}

void				RFC::onHandShake(::hpl::CallBack<RFC&> onHandShakeEvent) { _onHandShakeEvent = onHandShakeEvent; }
void				RFC::onMove(::hpl::CallBack<RFC&, RFC::Move const &> onMoveEvent) { _onMoveEvent = onMoveEvent; }
void				RFC::onShoot(::hpl::CallBack<RFC&, RFC::Shoot const &> onShootEvent) { _onShootEvent = onShootEvent; }
void				RFC::onColision(::hpl::CallBack<RFC&, RFC::Colision const &> onColisionEvent) { onColisionEvent = onColisionEvent; }
void				RFC::onHit(::hpl::CallBack<RFC&, RFC::HitMonster const &> onHitEvent) { _onHitEvent = onHitEvent; }
void				RFC::onKill(::hpl::CallBack<RFC&, RFC::HitMonster const &> onKillEvent) { _onKillEvent = onKillEvent; }


//void				RFC::setSocket(Socket &socket)
//{
//	_socket = &socket;
//	_socket->onRecive([this](Network::Socket &socket) {
//		if (_hasHandshake)
//			getData(socket);
//		else
//		{
//			ulint	size;
//			ulint	ret;
//
//			if ((size = socket.in().size()) < 6)
//				return;
//			char	*buff = new char[size];
//			ret = socket.in().read(buff, size);
//		}
//	});
//}
//
//void				RFC::getData(Socket &socket)
//{
//
//}