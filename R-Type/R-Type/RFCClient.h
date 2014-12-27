# pragma once

# include "IRFC.h"
//# include "Network/Client.h"

# define ASocket	Network::Socket

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
	ASocket	*_socket;

public:
	RFCClient();
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
		RECVSTARTGAME = 20,
		RECVCLIENTCRASH
	};


	void		setSocket(Socket &socket);
	void		getData(Socket &socket);

	void	sendHandshate(unsigned int idClient = 0); //6bytes
	void	sendMove(const sf::Vector2f &pos, const sf::Vector2f &direction); // 9bytes
	void	sendShoot(Weapon weapon, unsigned int idAmmo, const sf::Vector2f &pos, const sf::Vector2f &direction); // 12bytes
	void	sendCollision(unsigned int idClient, unsigned int idMonster, const sf::Vector2f &pos); // 9bytes
	void	sendHitMonster(unsigned int idMonster, const sf::Vector2f &posMonster); // 7bytes
	void	sendKillMonster(unsigned int idMonster, const sf::Vector2f &posMonster); // 7btytes

	void	recvCmd(Socket &socket);
	void	recvHandshate(Socket &socket);
	void	recvMove(Socket &socket);
	void	recvShoot(Socket &socket);
	void	recvCollision(Socket &socket);
	void	recvHitMonster(Socket &socket);
	void	recvKillMonster(Socket &socket);
	void	recvMonsterSpawn(Socket &socket);
	void	recvMonsterMove(Socket &socket);
	void	recvMonsterDestroy(Socket &socket);
	void	recvMonsterKillPlayer(Socket &socket);
	void	recvMonsterFire(Socket &socket);
	void	recvStartGame(Socket &socket);
	void	recvClientCrash(Socket &socket);
};