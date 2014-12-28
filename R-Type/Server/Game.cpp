#include "Game.h"

Game::Game()
{
	_dlLoader = new DlLoader(".");
	_frameRate.reset();
	_fireTime.reset();
	_spawn1 = true;
	_spawn2 = true;
}

Game::~Game() {}

void				Game::init()
{
	_dlLoader->loadDLL("MonsterType1", "monsterType1");
	_dlLoader->loadDLL("MonsterType2", "monsterType2");
}
#include <fstream>
void				Game::update(::hpl::Clock &time)
{
	IMonster::Dir	dir;
	sf::Vector2f	direction;
	float			t;
	int				i = 0;
	static int nb = 0;
	std::ofstream file("fichier.txt", std::ios_base::app);

	for (std::vector<IMonster *>::iterator it = _monster.begin(); it != _monster.end(); ++it)
	{
		dir = (*it)->update();
		if (_world.transformComponents[_idMonster[i]] != NULL && _world.movementComponents[_idMonster[i]] != NULL)
		{
			t = time.getElapsedTime().asFloat();
			if (t == 0)
				t = 0.02f;
			direction.x = dir.x - _monsterDir[i].x;
			direction.y = dir.y - _monsterDir[i].y;
//			file << direction.x << "  " << direction.y << std::endl;
			_monsterDir[i].x += direction.x * t * 80;
			_monsterDir[i].y += direction.y * t * 80;
			//direction = sf::Vector2f(dir.x, dir.y) - _world.transformComponents[_idMonster[i]]->position;
			//file << direction.x << "  " << direction.y << std::endl << std::endl;
			_world.movementComponents[_idMonster[i]]->direction = sf::Vector2f(direction.x, direction.y);
			if (nb == 0)
			{
				RFC::MonsterMove	mm;
				mm.idMonster = _idMonster[i];
				mm.coord.posX = dir.x;
				mm.coord.posY = dir.y;
				mm.dir.dirX = direction.x;
				mm.dir.dirY = direction.y;
				mm.orientation = 180.0;
				for (std::vector<RFC*>::iterator client = _rfcManager.rfc.begin(); client != _rfcManager.rfc.end(); ++client)
					(*client)->sendMonsterMove(mm);
			}
		}
		++i;
	}
	++nb;
	if (nb == 30)
		nb = 0;
}

void				Game::deleteMonster(int id)
{
	if (_world.transformComponents[_idMonster[id]]->position.x < -800)
	{
		_monster.erase(_monster.begin() + id);
		_idMonster.erase(_idMonster.begin() + id);
		_monsterDir.erase(_monsterDir.begin() + id);
//		_world.renderComponents[_idMonster[id]] = NULL;
	}
}

void				Game::run(::hpl::Clock &time)
{
	uint			id;

	update(time);
	for (unsigned i = 0; i < _monster.size(); ++i)
	{
		deleteMonster(i);
	}
	if (_frameRate.getElapsedTime().second() % 4)
	{
		if (_spawn1)
		{
			spawnMonster("monsterType1");
			_spawn1 = false;
		}
	}
	else
		_spawn1 = true;
	if (_frameRate.getElapsedTime().second() % 7)
	{
		if (_spawn2)
		{
			spawnMonster("monsterType2");
			_spawn2 = false;
		}
	}
	else
		_spawn2 = true;
	if (_fireTime.getElapsedTime().millisecond() > 350)
	{
		if (_monster.size() > 0)
		{
			id = rand() % _monster.size();
			if (_monster[id]->fire().x > 250)
			{
				fire(id);
				_fireTime.reset();
			}
		}
	}
}

void				Game::spawnMonster(std::string const &name)
{
	IMonster		*instance = NULL;
	IMonster::Dir	dir;
	uint			id = 0;
	float			x, y = 0;

	x = static_cast<float>(rand() % 200 + 1000);
	y = static_cast<float>(rand() % 500 + 10);
	dir.x = x;
	dir.y = y;
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
	_monsterDir.push_back(dir);
}

void				Game::fire(int id)
{
	uint			tmp;
	IMonster::Dir	dir;

	dir = _monster[id]->fire();
	tmp = _world.createEmptyEntity();
	_ressource.loadTexture(_monster[id]->getFire());
	_world.addRenderComponent(tmp, ComponentFactory::createRenderComponent(_ressource.getTexture(_monster[id]->getFire())));
	_world.addTransformComponent(tmp, ComponentFactory::createTransformComponent(sf::Vector2f(1021, 728), sf::Vector2f(dir.x, dir.y + 50), sf::Vector2f(0.01f, 0.01f)));
	_world.addMovementComponent(tmp, ComponentFactory::createMovementComponent(50, sf::Vector2f(-8, 0)));
	RFC::MonsterShoot	mm;
	mm.idMonster = id;
	mm.weapon = RFC::Weapon::W1;
	mm.coord.posX = dir.x;
	mm.coord.posY = dir.y;
	mm.dir.dirX = -8;
	mm.dir.dirY = 0;
	for (std::vector<RFC*>::iterator client = _rfcManager.rfc.begin(); client != _rfcManager.rfc.end(); ++client)
		(*client)->sendMonsterFire(mm);
}

World				&Game::getWorld() { return (_world); }
