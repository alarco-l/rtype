#pragma once

#include <string>

#include "basictypes.h"

namespace hpl
{
	template<typename ...Args> struct Arguments {
		static const ulint size = sizeof...(Args);
	};

	template <typename ...Args> struct String
	{
		static char **toTable(Args ...args)
		{
			char	**table = new char*[Utils::Arguments<Args...>::size + 1];

			String<Args...>::tableFeed(table, 0, args...);
			return (table);
		}

		static void	deleteTable(char **table)
		{
			for (ulint it = 0; table[it]; ++it)
				delete (table[it]);
			delete (table);
		}

		static char	*toChar(std::string const &string)
		{
			char	*str = new char[string.length() + 1];
			ulint	it;

			for (it = 0; it < string.length(); ++it)
				str[it] = string[it];
			str[it] = 0;
			return (str);
		}

		static void	deleteChar(char *str)
		{
			delete (str);
		}

	private:
		template <typename ...ArgsS> static void	tableFeed(char **&table, ulint it, std::string const &first, ArgsS ...args)
		{
			String<Args...>::tableFeed(table, it + 1, args...);
			table[it] = String::toChar(first);
		}

		static void	tableFeed(char **&table, ulint it)
		{
			table[it] = NULL;
		}
	};

	class Operators
	{
	public:
		template <typename Type, typename ...Args> static Type	Min(Type const &value1, Type const &value2, Args ...args) { return (value1 < value2 ? Min<Type>(value1, args...) : Min<Type>(value2, args...)); }
		template <typename Type> static Type	Min(Type const &value1, Type const &value2) { return (value1 < value2 ? value1 : value2); }
	};

	namespace Inheritance
	{
		template <typename Parent, typename Child> class IsInherit
		{
			class No {};
			class Yes { No no[3]; };

			static Yes	is(Parent *);
			static No	is(...);

			static void	constraints(Child *ptr)
			{
				Parent	*ptrTo = ptr;
				ptrTo = ptr;
			}

		public:
			enum
			{
				value = sizeof(is(static_cast<Child*>(0))) == sizeof(Yes)
			};

			IsInherit(void)
			{
				void(*funcPtr)(Child*) = constraints;
			}
		};

		template <typename T1, typename T2> struct IsSame { enum { value = 0 }; };
		template <typename T1> struct IsSame < T1, T1 > { enum { value = 1 }; };
	}

	template <typename Type> struct RemoveReference { typedef Type type; };
	template <typename Type> struct RemoveReference<Type&> { typedef Type type; };
	template <typename Type> struct RemoveReference<Type&&> { typedef Type type; };

	template <typename Type> Type	&&forward(RemoveReference<Type> &arg) { return (static_cast<_Ty&&>(_arg)); }
	template <typename Type> Type	&&forward(RemoveReference<Type> &&arg) { return (static_cast<_Ty&&>(_arg)); }
}