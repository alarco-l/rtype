#include "RFC.h"

RFC::RFC(Network::Socket &socket) : _hasHandshake(false), _socket(&socket)
{
	_socket->onRecive(::hpl::bind(&RFC::recvCmd, this, ::hpl::Placeholder::_1));
}
RFC::~RFC() {}
#include <iostream>
void				RFC::recvCmd(Network::Socket &socket) {
	//static int i = 0;
	//std::fstream tata("tata.txt", std::fstream::in | std::fstream::app);
	char buff;
	int nb = socket.in().get(&buff, 1);
	RFC::RecvCommand cmd = (RFC::RecvCommand)buff;

	switch (cmd)
	{
	case RFC::RECVHANDSHAKE:
		break;
	case RFC::RECVMOVE:
		char buffMove[8];
		RFC::Move mov;
		nb = socket.in().get(buffMove, 8);
		mov.coord.posX = *(short int*)(buffMove);
		mov.coord.posY = *(short int*)(buffMove + 2);
		mov.dir.dirX = *(short int*)(buffMove + 4);
		mov.dir.dirY = *(short int*)(buffMove + 6);
		if (_onMoveEvent)
			_onMoveEvent(*this, mov);
	case RFC::RECVSHOOT:
		char buffShoot[10];
		RFC::Shoot shoot;
		nb = socket.in().get(buffShoot, 10);
		shoot.idMuni = *(short int*)(buffShoot);
		shoot.coord.posX = *(short int*)(buffShoot + 2);
		shoot.coord.posY = *(short int*)(buffShoot + 4);
		shoot.dir.dirX = *(short int*)(buffShoot + 6);
		shoot.dir.dirY = *(short int*)(buffShoot + 8);
		if (_onShootEvent)
			_onShootEvent(*this, shoot);
		break;
	case RFC::RECVCOLLISION:
		char buffColision[8];
		RFC::Colision colision;
		nb = socket.in().get(buffColision, 8);
		colision.idOnColision1 = *(short int*)(buffColision);
		colision.idOnColision2 = *(short int*)(buffColision + 2);
		colision.coord.posX = *(short int*)(buffColision + 4);
		colision.coord.posY = *(short int*)(buffColision + 6);
		if (_onColisionEvent)
			_onColisionEvent(*this, colision);
		break;
	case RFC::RECVHITMONSTER:
		char buffHitMonster[6];
		RFC::HitMonster hitMonster;
		nb = socket.in().get(buffHitMonster, 6);
		hitMonster.idMonster = *(short int*)(buffHitMonster);
		hitMonster.coord.posX = *(short int*)(buffHitMonster + 2);
		hitMonster.coord.posY = *(short int*)(buffHitMonster + 4);
		if (_onHitEvent)
			_onHitEvent(*this, hitMonster);
		break;
	case RFC::RECVKILLMONSTER:
		char buffKillMonster[6];
		RFC::HitMonster killMonster;
		nb = socket.in().get(buffKillMonster, 6);
		killMonster.idMonster = *(short int*)(buffKillMonster);
		killMonster.coord.posX = *(short int*)(buffKillMonster + 2);
		killMonster.coord.posY = *(short int*)(buffKillMonster + 4);
		if (_onKillEvent)
			_onKillEvent(*this, killMonster);
		break;
	default:
		break;
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
	char c = RFC::SENDMOVE;
	_socket->out().write(&c, 1);
	
	usint tmp = (short int)(move.idMonster);
	_socket->out().write((char *)&tmp, sizeof(short int));
	tmp = (short int)(move.coord.posX);
	_socket->out().write((char *)&tmp, sizeof(short int));
	tmp = (short int)(move.coord.posY);
	_socket->out().write((char *)&tmp, sizeof(short int));
	tmp = (short int)(move.dir.dirX);
	_socket->out().write((char *)&tmp, sizeof(short int));
	tmp = (short int)(move.dir.dirY);
	_socket->out().write((char *)&tmp, sizeof(short int));
	tmp = (short int)(move.orientation);
	_socket->out().write((char *)&tmp, sizeof(short int));
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
	tmp = (short int)(shoot.coord.posX);
	_socket->out().write((char *)&tmp, sizeof(short int));
	tmp = (short int)(shoot.coord.posY);
	_socket->out().write((char *)&tmp, sizeof(short int));
	tmp = (short int)(shoot.dir.dirX);
	_socket->out().write((char *)&tmp, sizeof(short int));
	tmp = (short int)(shoot.dir.dirY);
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