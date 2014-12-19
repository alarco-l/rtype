#pragma once

#include "basictypes.h"

namespace hpl
{
	template <typename TFunc> class Function;

	template <typename TRet, typename ...TArgs> struct _IPointer
	{
		virtual TRet	operator()(TArgs ...args) = 0;
		virtual _IPointer<TRet, TArgs...>	*clone(void) = 0;
	};
	template <typename ...TArgs> struct _IPointer<void, TArgs...>
	{
		virtual void	operator()(TArgs ...args) = 0;
		virtual _IPointer<void, TArgs...>	*clone(void) = 0;
	};

	template <typename TPtr, typename TRet, typename ...TArgs> struct _Pointer : public _IPointer < TRet, TArgs... >
	{
		_Pointer(TPtr ptr) : _ptr(ptr) {}
		TRet	operator()(TArgs ...args) { return (_ptr(args...)); }
		_IPointer<TRet, TArgs...>	*clone(void) { return (new _Pointer<TPtr, TRet, TArgs...>(_ptr)); }
		TPtr	_ptr;
	};
	template <typename TPtr, typename ...TArgs> struct _Pointer<TPtr, void, TArgs...> : public _IPointer < void, TArgs... >
	{
		_Pointer(TPtr ptr) : _ptr(ptr) {}
		void	operator()(TArgs ...args) { _ptr(args...); }
		_IPointer<void, TArgs...>	*clone(void) { return (new _Pointer<TPtr, void, TArgs...>(_ptr)); }
		TPtr	_ptr;
	};

	template <typename TRet, typename ...TArgs> class _FunctionBase
	{
		_IPointer<TRet, TArgs...>	*_func;
	public:
		_FunctionBase(void) : _func(NULL) {}
		template <typename Type> void assign(Type func)
		{
			if (_func) delete _func;
			_func = new _Pointer<Type, TRet, TArgs...>(func);
		}
		template <typename Type> void assign(::hpl::Function<Type> const &func)
		{
			if (_func) delete _func;
			_func = new _Pointer<Type, TRet, TArgs...>(func._func->clone());
		}
		TRet	operator()(TArgs ...args) { return ((*_func)(args...)); }
	};
	template <typename ...TArgs> class _FunctionBase < void, TArgs... >
	{
		_IPointer<void, TArgs...>	*_func;
	public:
		_FunctionBase(void) : _func(NULL) {}
		template <typename Type> void	assign(Type func)
		{
			if (_func) delete _func;
			_func = new _Pointer<Type, void, TArgs...>(func);
		}
		template <typename Type> void assign(::hpl::Function<Type> const &func)
		{
			if (_func) delete _func;
			_func = new _Pointer<Type, void, TArgs...>(func._func->clone());
		}
		void	operator()(TArgs ...args) { (*_func)(args...); }
	};
	template <typename TFunc> struct _Function;
	template <typename TRet, typename ...TArgs> struct _Function < TRet(TArgs...) > { typedef _FunctionBase<TRet, TArgs...> type; };

	template <typename TFunc> class Function : public _Function<TFunc>::type
	{
		typedef typename _Function<TFunc>::type	_Base;
	public:
		Function(void) {}
		template <typename Type> Function(Type func) { assign(func); }
		template <typename Type> Function(::hpl::Function<Type> const &func) { assign(func); }

		template <typename Type> Function<TFunc>	&operator=(::hpl::Function<Type> const &func) { assign(func); return (*this); }
	};

	template <typename ...Type> using CallBack = ::hpl::Function < void(Type...) > ;
	typedef ::hpl::Function<void(void)>	Call;



	namespace Placeholder
	{
		template <int value> struct _Ph {};
#define PH(x) extern _Ph<##x>	_##x
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

	template <class Class, typename TRet, typename ...Args> class Pointer
	{
		TRet(Class::*_func)(Args...);
		Class		*_class;

	public:
		Pointer(TRet(Class::*func)(Args...), Class *clas) : _func(func), _class(clas) {}

		template <typename ...Args> TRet	operator()(Args ...args) { return ((_class->*_func)(args...)); }
	};
	template <class Class, typename ...Args> class Pointer < Class, void(Class::*)(Args...) >
	{
		void(Class::*_func)(Args...);
		Class		*_class;

	public:
		Pointer(void(Class::*func)(Args...), Class *clas) : _func(func), _class(clas) {}

		template <typename ...Args> void	operator()(Args ...args) { (_class->*_func)(args...); }
	};

	template <typename ...Elements> struct Storage;
	template <typename _Element, typename ..._Others> struct Storage<_Element, _Others...> : public Storage<_Others...>
	{
		typedef typename Storage<_Element, _Others...>	MySelf;
		typedef typename Storage<_Others...>			NextElement;
		typedef typename _Element						ElementType;

		template <ullint element>	struct GetElement { typedef typename NextElement::template GetElement<element - 1>::ElementType ElementType; };
		template <>					struct GetElement<0> { typedef typename ElementType ElementType; };

		Storage(_Element &element, _Others ...others) : _element(element), NextElement(others...) {}

		template <ullint element>	typename GetElement<element>::ElementType		&get(void) { return (NextElement::get<element - 1>()); }
		template <>					typename GetElement<0>::ElementType				&get<0>(void) { return (_element); }
		template <ullint element>	typename GetElement<element>::ElementType const	&get(void) const { return (NextElement::get<element - 1>()); }
		template <>					typename GetElement<0>::ElementType const		&get<0>(void) const { return (_element); }

		template <typename Type>	Type												&operator[](Type &value) { return (value); }
		template <ullint element>	typename GetElement<element - 1>::ElementType		&operator[](::hpl::Placeholder::_Ph<element> &ph) { return (get<element - 1>()); }
		template <typename Type>	Type const											&operator[](Type &value) const { return (value); }
		template <ullint element>	typename GetElement<element - 1>::ElementType const	&operator[](::hpl::Placeholder::_Ph<element> &ph) const { return (get<element - 1>()); }

	private:
		_Element	_element;
	};


	template <> struct Storage<>
	{
		template <ullint element>	struct GetElement { typedef void *ElementType; };

		Storage() {}

		template <typename Type>	Type												&operator[](Type &value) { return (value); }
		template <typename Type>	Type const											&operator[](Type &value) const { return (value); }
	};

	template <typename _Storage, typename _Callable, typename _TRet, ullint _nbArgs> class _Bind
	{
		_Storage	_storage;
		_Callable	_callable;

		template <ullint currentArg>	struct Call				{ template <typename CallArgs, typename ...Args> static _TRet	call(_Callable &callable, _Storage &storArgs, CallArgs &callArgs, Args &...args) { return (Call<currentArg + 1>::call(callable, storArgs, callArgs, args..., callArgs[storArgs.get<currentArg>()])); } };
		template <>						struct Call<_nbArgs>	{ template <typename CallArgs, typename ...Args> static _TRet	call(_Callable &callable, _Storage &storArgs, CallArgs &callArgs, Args &...args) { return (callable(args...)); } };

	public:
		_Bind(_Storage &Storage, _Callable &callable) : _storage(Storage), _callable(callable) {}

		template <typename ...Args> _TRet	operator()(Args &&...args)
		{
			Storage<Args...>	callArgs(args...);
			return (Call<0>::call(_callable, _storage, callArgs));
		}
	};

	template <typename _Storage, typename _Callable, ullint _nbArgs> class _Bind<_Storage, _Callable, void, _nbArgs>
	{
		_Storage	_storage;
		_Callable	_callable;

		template <ullint currentArg>	struct Call				{ template <typename CallArgs, typename ...Args> static void	call(_Callable &callable, _Storage &storArgs, CallArgs &callArgs, Args &...args) { Call<currentArg + 1>::call(callable, storArgs, callArgs, args..., callArgs[storArgs.get<currentArg>()]); } };
		template <>						struct Call<_nbArgs>	{ template <typename CallArgs, typename ...Args> static void	call(_Callable &callable, _Storage &storArgs, CallArgs &callArgs, Args &...args) { callable(args...); } };

	public:
		_Bind(_Storage &Storage, _Callable &callable) : _storage(Storage), _callable(callable) {}

		template <typename ...Args> void	operator()(Args &&...args)
		{
			Storage<Args...>	callArgs(args...);
			Call<0>::call(_callable, _storage, callArgs);
		}
	};

	template <typename Func> struct Callable;
	template <typename TRet, typename ...Args> struct Callable<TRet(*)(Args...)>
	{
		using type = TRet(*)(Args...);
		typedef TRet	ret;
	};


	template <typename ...Args> struct Arguments { static const ullint count = sizeof...(Args); };

	template <typename Func, typename ...Args>	_Bind<Storage<Args...>, typename Callable<Func>::type, typename Callable<Func>::ret, Arguments<Args...>::count>	bind(Func func, Args &&...args)
	{
		return (_Bind<Storage<Args...>, typename Callable<Func>::type, typename Callable<Func>::ret, Arguments<Args...>::count>(Storage<Args...>(args...), func));
	}

	template <typename TRet, class Class, typename ...Args, typename ...Params>	_Bind<Storage<Args...>, Pointer<Class, TRet, Args...>, TRet, Arguments<Args...>::count>	bind(TRet(Class::*func)(Args...), Class *clas, Params &&...args)
	{
		return (_Bind<Storage<Args...>, Pointer<Class, TRet, Args...>, TRet, Arguments<Args...>::count>(Storage<Args...>(args...), Pointer<Class, TRet, Args...>(func, clas)));
	}
}
