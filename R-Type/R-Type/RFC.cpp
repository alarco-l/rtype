#include "RFC.h"

RFC::RFC() : _hasHandshake(false), _socket(NULL) {}
RFC::~RFC() {}

void				RFC::sendStartGame(sint munition1, sint munition2) { }
void				RFC::sendClientCrash(sint idClient) { }
void				RFC::sendMonsterSpawn(RFC::MonsterSpawn) { }
void				RFC::sendMonsterMove(RFC::MonsterMove) { }
void				RFC::sendMonsterDestroy(RFC::HitMonster) { }
void				RFC::sendMonsterFire(RFC::MonsterShoot) { }
void				RFC::sendMonsterKillPlayer(RFC::MonsterKillPlayer) { }
void				RFC::sendNewMunition(sint munition) { }

void				RFC::onHandShake(Callback<RFC&> onHandShakeEvent) { _onHandShakeEvent = onHandShake; }
void				RFC::onMove(Callback<RFC&, RFC::Move const &> onMoveEvent) { _onMoveEvent = onMoveEvent; }
void				RFC::onShoot(Callback<RFC&, RFC::Shoot const &> onShootEvent) { _onShootEvent = onShootEvent; }
void				RFC::onColision(Callback<RFC&, RFC::Colision const &> onColisionEvent) { onColisionEvent = onColisionEvent; }
void				RFC::onHit(Callback<RFC&, RFC::HitMonster const &> onHitEvent) { _onHitEvent = onHitEvent; }
void				RFC::onKill(Callback<RFC&, RFC::HitMonster const &> onKillEvent) { _onKillEvent = onKillEvent; }

void				RFC::setSocket(Socket &socket)
{
	_socket = &socket;
	_socket->onRecive([this](Network::Socket &socket) {
		if (_hasHandshake)
			getData(socket);
		else
		{
			ulint	size;
			ulint	ret;

			if ((size = socket.in().size()) < 6)
				return;
			char	*buff = new char[size];
			ret = socket.in().read(buff, size);
		}
	});
}

void				RFC::getData(Socket &socket)
{

}