#include "Game.h"

Game::Game()
{
	_dlLoader = new DlLoader(".");
	_time.restart();
	_spawn1 = true;
	_spawn2 = true;
}

Game::~Game() {}

void				Game::init()
{
	_dlLoader->loadDLL("MonsterType1", "monsterType1");
	_dlLoader->loadDLL("MonsterType2", "monsterType2");
}

void				Game::update()
{
	IMonster::Dir	dir;
	sf::Vector2f	direction;
	int				i = 0;

	for (std::vector<IMonster *>::iterator it = _monster.begin(); it != _monster.end(); ++it)
	{
		dir = (*it)->update();
		if (_world.transformComponents[_idMonster[i]] != NULL && _world.movementComponents[_idMonster[i]] != NULL)
		{
			direction = sf::Vector2f(dir.x, dir.y) - _world.transformComponents[_idMonster[i]]->position;
			_world.movementComponents[_idMonster[i]]->direction = sf::Vector2f(direction.x, direction.y);
		}
		++i;
	}
}

void				Game::deleteMonster(int id)
{
	if (_world.transformComponents[_idMonster[id]]->position.x < -1500)
	{
		_monster.erase(_monster.begin() + id);
		_idMonster.erase(_idMonster.begin() + id);
		_world.renderComponents[_idMonster[id]] = NULL;
	}
}

void				Game::run()
{
	update();
	for (unsigned i = 0; i < _monster.size(); ++i)
	{
		deleteMonster(i);
	}
	if ((int)_time.getElapsedTime().asSeconds() % 2)
	{
		if (_spawn1)
		{
			spawnMonster("monsterType1");
			_spawn1 = false;
		}
	}
	else
		_spawn1 = true;
	if ((int)_time.getElapsedTime().asSeconds() % 3)
	{
		if (_spawn2)
		{
			spawnMonster("monsterType2");
			_spawn2 = false;
		}
	}
	else
		_spawn2 = true;
}

void				Game::spawnMonster(std::string const &name)
{
	IMonster		*instance = NULL;
	uint			id;
	float			x, y = 0;

	x = rand() % 200 + 1000;
	y = rand() % 500 + 10;
	try {
		instance = _dlLoader->getInstance<IMonster>(name);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	if (!instance)
		return;
	instance->setSpawn(x, y);
	_monster.push_back(instance);
	id = _world.createEmptyEntity();
	_ressource.loadTexture(instance->getTexture());
	_world.addRenderComponent(id, ComponentFactory::createRenderComponent(_ressource.getTexture(instance->getTexture())));
	_world.addTransformComponent(id, ComponentFactory::createTransformComponent(sf::Vector2f(1021, 728), sf::Vector2f(x, y), sf::Vector2f(0.05f, 0.20f)));
	_world.addMovementComponent(id, ComponentFactory::createMovementComponent(50, sf::Vector2f(0, 0)));
	_idMonster.push_back(id);
}

World				&Game::getWorld() { return (_world); }
