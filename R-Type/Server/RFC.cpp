#include "RFC.h"

RFC::RFC(Network::Socket &socket) : _hasHandshake(false), _socket(&socket) {}
RFC::~RFC() {}

void				RFC::recvCmd(RFC::RecvCommand cmd, Network::Socket &socket) {
	//static int i = 0;
	//std::fstream tata("tata.txt", std::fstream::in | std::fstream::app);
	int nb;

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
		_onShootEvent(*this, shoot);
		break;
	case RFC::RECVCOLLISION:
		char buffColision[8];
		RFC::Colision colision;
		nb = socket.in().get(buffColision, 10);
		colision.idOnColision1 = *(short int*)(buffColision);
		colision.idOnColision2 = *(short int*)(buffColision + 2);
		colision.coord.posX = *(short int*)(buffColision + 4);
		colision.coord.posY = *(short int*)(buffColision + 6);
		_onColisionEvent(*this, colision);
		break;
	case RFC::RECVHITMONSTER:
		break;
	case RFC::RECVKILLMONSTER:
		break;
	default:
		break;
	}
}

void				RFC::sendStartGame(sint munition1, sint munition2) { }
void				RFC::sendClientCrash(sint idClient) { }
void				RFC::sendMonsterSpawn(RFC::MonsterSpawn) { }
void				RFC::sendMonsterMove(RFC::MonsterMove) { }
void				RFC::sendMonsterDestroy(RFC::HitMonster) { }
void				RFC::sendMonsterFire(RFC::MonsterShoot) { }
void				RFC::sendMonsterKillPlayer(RFC::MonsterKillPlayer) { }
void				RFC::sendNewMunition(sint munition) { }

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