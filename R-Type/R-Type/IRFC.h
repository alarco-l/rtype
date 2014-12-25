#pragma once

#include "BasicType.h"

#include "Network/Client.h"
#define Socket	Network::Socket

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

	virtual void		setSocket(Socket &socket) = 0;
	virtual void		getData(Socket &socket) = 0;
};