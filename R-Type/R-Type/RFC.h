#pragma once

#include <vector>

#include "IRFC.h"

class						RFC : public IRFC
{
public:
	enum					Monster
	{
		M1,
		M2,
		M3,
		M4,
		M5
	};

	enum					Weapon
	{
		W1,
		W2,
		W3,
		W4,
		W5
	};

	struct					Move
	{
		sint				idPlayer;
		Coord				coord;
		Dir					dir;
	};

	struct					Shoot
	{
		Coord				coord;
		Dir					dir;
		sint				idMuni;
	};

	struct					Colision
	{
		Coord				coord;
		sint				idOnColision1;
		sint				idOnColision2;
	};

	struct					HitMonster
	{
		sint				idMonster;
		Coord				coord;
	};

	struct					MonsterSpawn
	{
		Monster				type;
		sint				idMonster;
		Coord				coord;
	};

	struct					MonsterMove
	{
		sint				idMonster;
		Coord				coord;
		Dir					dir;
		sint				orientation;
	};

	struct					MonsterShoot
	{
		Weapon				weapon;
		sint				idMonster;
		Coord				coord;
		Dir					dir;
	};

	struct					MonsterKillPlayer
	{
		sint				idClient;
		Coord				coord;
	};

	RFC();
	~RFC();

	void					sendStartGame(sint munition1, sint munition2);
	void					sendClientCrash(sint idClient);
	void					sendMonsterSpawn(RFC::MonsterSpawn);
	void					sendMonsterMove(RFC::MonsterMove);
	void					sendMonsterDestroy(RFC::HitMonster);
	void					sendMonsterFire(RFC::MonsterShoot);
	void					sendMonsterKillPlayer(RFC::MonsterKillPlayer);
	void					sendNewMunition(sint munition);

	void					onHandShake(Callback<RFC&> onHandShakeEvent);
	void					onMove(Callback<RFC&, RFC::Move const &> onMoveEvent);
	void					onShoot(Callback<RFC&, RFC::Shoot const &> onShootEvent);
	void					onColision(Callback<RFC&, RFC::Colision const &> onColisionEvent);
	void					onHit(Callback<RFC&, RFC::HitMonster const &> onHitEvent);
	void					onKill(Callback<RFC&, RFC::HitMonster const &> onKillEvent);

	void					setSocket(Socket &socket);
private:
	void					getData(Socket &socket);

	bool					_hasHandshake;
	std::vector<sint>		_idClient;

	Socket					*_socket;

	Callback<RFC&>								_onHandShakeEvent;
	Callback<RFC&, RFC::Move const &>			_onMoveEvent;
	Callback<RFC&, RFC::Shoot const &>			_onShootEvent;
	Callback<RFC&, RFC::Colision const &>		_onColisionEvent;
	Callback<RFC&, RFC::HitMonster const &>		_onHitEvent;
	Callback<RFC&, RFC::HitMonster const &>		_onKillEvent;
};