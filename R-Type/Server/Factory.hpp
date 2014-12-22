#  pragma once

# include <map>
# include <string>


template<class Base>
class Instance
{
public:
	virtual Base *create() = 0;
	virtual ~Instance() {}
};

template<class Base, class Object>
class NewInstance : public Instance < Base >
{
public:
	Base *create()
	{
		return (new Object());
	}
};

template<class Base>
class Factory
{
public:
	static void registerClass(const std::string& key, Instance<Base>* obj)
	{
		_map[key] = obj;
	}

	template<class Object>
	static void registerClass(const std::string& key)
	{
		registerClass(key, new NewInstance<Base, Object>());
	}

	static Base *create(const std::string& id)
	{
		return _map.at(id)->create();
	}

	static void releaseAll()
	{
		typename std::map<std::string, Instance<Base>*>::iterator it = _map.begin();

		while (it != _map.end())
			_map.erase(it++);
	}
private:
	static std::map<std::string, Instance<Base>*> _map;
};

template <class Base> std::map<std::string, Instance<Base>*> Factory<Base>::_map;