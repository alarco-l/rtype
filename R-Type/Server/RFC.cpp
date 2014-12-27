#include "RFC.h"

RFC::RFC(Network::Socket &socket) : _hasHandshake(false), _socket(&socket) {}
RFC::~RFC() {}

void				RFC::recvCmd(RFC::RecvCommand cmd, Network::Socket &socket) {
	//static int i = 0;
	//std::fstream tata("tata.txt", std::fstream::in | std::fstream::app);
	int nb;
	IRFC::Dir		dir;
	IRFC::Coord		coord;

	switch (cmd)
	{
	case RFC::RECVHANDSHAKE:
		break;
	case RFC::RECVMOVE:
		char buff[8];
		RFC::Move mov;


		nb = socket.in().get(buff, 8);
		mov.coord.posX = *(short int*)(buff);
		mov.coord.posY = *(short int*)(buff + 2);
		mov.dir.dirX = *(short int*)(buff + 4);
		mov.dir.dirY = *(short int*)(buff + 6);
		//_onMoveEvent(*this, )
		//tata << i++ << "------------------------------------------" << std::endl;
		//tata << cmd << " x =" << coord.posX << "\ny =" << coord.posY << "\ndirX =" << dir.dirX << "\ndirY =" << dir.dirY << std::endl;
	case RFC::RECVSHOOT:
		break;
	case RFC::RECVCOLLISION:
		break;
	case RFC::RECVHITMONSTER:
		break;
	case RFC::RECVKILLMONSTER:
		break;
	default:
		break;
	}
	//tata.close();
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