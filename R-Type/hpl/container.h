#pragma once

#include <list>
#include <map>

namespace hpl
{
	namespace Container
	{
		template <typename Type> using Dynamic = ::std::list<Type>;
		template <typename Type1, typename Type2> using Associative = ::std::map<Type1, Type2>;
	}
}