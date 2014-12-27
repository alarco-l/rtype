#pragma once

#include "BasicType.h"

#include "Network/Client.h"

class					IRFC
{
public:

	struct					Coord
	{
		sint				posX;
		sint				posY;
	};

	struct					Dir
	{
		sint				dirX;
		sint				dirY;
	};

	virtual				~IRFC() {}

	//virtual void		setSocket(Network::Socket &socket) = 0;
	//virtual void		getData(Network::Socket &socket) = 0;
};