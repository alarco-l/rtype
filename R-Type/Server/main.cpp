#include "Game.h"

#include "RFC.h"
#include "hpl.h"

#include "RFCManager.h"

int		main(int argc, char *argv[], char *env[])
{
	Game			game;
	sf::Clock		clock;
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	try {
		game.init();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	::hpl::Clock	frameRate;
	while (1)
	{
		frameRate.reset();
		game.run(frameRate);
		::hpl::Time t = ::hpl::Time::Millisecond(20) - frameRate.getElapsedTime();
		if (t.millisecond() > 0)
			::hpl::Process::sleep(t);
	}
	return(0);
}