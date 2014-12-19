#include "function.hpp"

namespace hpl
{
	namespace Placeholder
	{
#define PH(x) _Ph<##x>	_##x
		PH(1);
		PH(2);
		PH(3);
		PH(4);
		PH(5);
		PH(6);
		PH(7);
		PH(8);
		PH(9);
		PH(10);
		PH(11);
		PH(12);
		PH(13);
		PH(14);
		PH(15);
		PH(16);
		PH(17);
		PH(18);
		PH(19);
		PH(20);
#undef PH
	}
}