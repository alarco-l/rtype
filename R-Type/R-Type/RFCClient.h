# pragma once

# include "IRFC.h"
# include "Network/Client.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <map>
#include "GameSpecificFactory.h"
#include "World.h"

class Game;

class RFCClient : public IRFC
{
private:
	enum idPlayer
	{
		PLAYER1,
		PLAYER2,
		PLAYER3,
		PLAYER4,
		PLAYERMAX,
	};
	enum Monster
	{
		MONSTER1,
		MONSTER2,
		MONSTER3,
		MONSTER4,
		MONSTERMAX,
	};
	enum Weapon
	{
		WEAPON1,
		WEAPON2,
		WEAPON3,
		WEAPONMAX
	};
	bool	_handshate;
	bool	_isConnect;
	short int	_id[4];
	short int	_idClientCrash;
	//RecvCommand _recvCmd;
	Network::Socket	*_socket;

	std::map<unsigned int, unsigned int> _rfcToWorldId;
	std::map<unsigned int, unsigned int> _worldToRfcId;

	GameSpecificFactory &_factory;
	World &_world;
	Game	*_game;

public:
	RFCClient(Network::Socket &socket, GameSpecificFactory &factory, World &world, Game *game);
	~RFCClient();
	
	enum SendCommand
	{
		SENDHANDSHAKE,
		SENDMOVE,
		SENDSHOOT,
		SENDCOLLISION,
		SENDHITMONSTER,
		SENDKILLMONSTER
	};

	enum RecvCommand
	{
		RECVHANDSHAKE,
		RECVMOVE,
		RECVSHOOT,
		RECVCOLLISION,
		RECVHITMONSTER,
		RECVKILLMONSTER,
		RECVMONSTERSPAWN,
		RECVMONSTERMOVE,
		RECVMONSTERDESTROY,
		RECVMONSTERFIRE,
		RECVMONSTERKILLPLAYER,
		RECVMUNITIONS,
		RECVSTARTGAME = 20,
		RECVCLIENTCRASH
	};

	void	sendHandshake(unsigned int idClient = 0); //6bytes
	void	sendMove(const sf::Vector2f &pos, const sf::Vector2f &direction); // 9bytes
	void	sendShoot(Weapon weapon, unsigned int idAmmo, const sf::Vector2f &pos, const sf::Vector2f &direction); // 12bytes
	void	sendCollision(unsigned int idClient, unsigned int idMonster, const sf::Vector2f &pos); // 9bytes
	void	sendHitMonster(unsigned int idMonster, const sf::Vector2f &posMonster); // 7bytes
	void	sendKillMonster(unsigned int idMonster, const sf::Vector2f &posMonster); // 7btytes

	void	recvCmd(Network::Socket &socket);
	void	recvHandshake(const char *); 
	void	recvMove(const char *);
	void	recvMunitions(const char *);
	void	recvShoot(const char *);
	void	recvCollision(const char *);
	void	recvHitMonster(const char *);
	void	recvKillMonster(const char *);
	void	recvMonsterSpawn(const char *);
	void	recvMonsterMove(const char *);
	void	recvMonsterDestroy(const char *);
	void	recvMonsterKillPlayer(const char *);
	void	recvMonsterFire(const char *);
	void	recvStartGame(const char *);
	void	recvClientCrash(const char *);
};

#include "Game.h"
