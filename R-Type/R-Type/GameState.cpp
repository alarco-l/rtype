#include "GameState.h"
#include "GUIPauseState.h"
#include "GUIEndState.h"
#include "RFCClient.h"

GameState::GameState(Game *game) : AState(game)
{
	game->_rfc = &_rfc;
	_isBlocking = true;
}

GameState::~GameState() {}

void	GameState::onConnectEvent(Network::Client &client)
{
	_rfc = new RFCClient(client.socket);
	//client.socket.onRecive(::hpl::bind(&GameState::onRecive, this, ::hpl::Placeholder::_1));
	client.socket.onEnd(::hpl::bind(&GameState::onEnd, this, ::hpl::Placeholder::_1));
}

void	GameState::onRecive(Network::Socket &socket) {}
void	GameState::onEnd(Network::Socket const &socket) {}

void						GameState::initialize()
{
	_client = Network::Client::connect<Network::udp::ip4>(Network::Client::Config("127.0.0.1", 2222), ::hpl::bind(&GameState::onConnectEvent, this, ::hpl::Placeholder::_1));
	_game->factory.createGameBackground(_idBackground, _world, _game->getScreenSize());
	_game->factory.createHUD(_idHud, _world, _game->getScreenSize());
	_game->factory.createPlayer(_idPlayer, _world);
}

void						GameState::stop(void)
{
	//_client->socket.close();
}

bool						GameState::handleKeyEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		_game->pushState(new GUIPauseState(_game));
		return (true);
	}

	// simuler une fin de partie
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
		_game->pushState(new GUIEndState(_game, GUIEndState::LOSE));
		return (true);
	}
	return (true);
}

bool						GameState::handleKeyState()
{
	sf::Vector2f			direction = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f			size = _world.transformComponents[_idPlayer[RType::Player::SHIP]]->size;
	sf::Vector2f			scale = _world.transformComponents[_idPlayer[RType::Player::SHIP]]->scale;
	sf::Vector2f			pos = _world.transformComponents[_idPlayer[RType::Player::SHIP]]->position;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pos.y > 0)
		direction += sf::Vector2f(0, -1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pos.y < _game->getScreenSize().y - (size.y * scale.y))
		direction += sf::Vector2f(0, 1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pos.x > 0)
		direction += sf::Vector2f(-1, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pos.x < _game->getScreenSize().x - (size.x * scale.x))
		direction += sf::Vector2f(1, 0);

	_world.movementComponents[_idPlayer[RType::Player::SHIP]]->direction = direction;
	_rfc->sendMove(_world.transformComponents[_idPlayer[RType::Player::SHIP]]->position, direction);

	// pan pan
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		_world.weaponComponents[_idPlayer[RType::Player::WEAPON_1]]->fire = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		_world.weaponComponents[_idPlayer[RType::Player::WEAPON_2]]->fire = true;

	return (true);
}

void						GameState::update(const sf::Time &elapsed)
{
	TimerSystem::update(_world, elapsed);
	WeaponSystem::update(_world, elapsed, _game->factory, _game->getScreenSize());
	ParticleSystem::update(_world, elapsed);
	TransformSystem::update(_world, elapsed, _game->getScreenSize());
	CollisionSystem::update(_world, sf::Vector2u(10, 10), _game->getScreenSize());
	HealthSystem::update(_world, elapsed, _game->factory);
	AnimationSystem::update(_world, elapsed);
	DeathSystem::update(_world);
	this->updateBackground();

	// Si vous voulez savoir ce que ça fait, commentez le et essayez d'appuyer sur echap et de bouger en meme temps ingame
	_world.movementComponents[_idPlayer[RType::Player::SHIP]]->direction = sf::Vector2f(0.0f, 0.0f);
}


void						GameState::updateBackground()
{
	if (_world.transformComponents[_idBackground[RType::GameBackground::DEFAULT]]->position.x + _world.transformComponents[_idBackground[RType::GameBackground::DEFAULT]]->size.x <= 0.0f)
		_world.transformComponents[_idBackground[RType::GameBackground::DEFAULT]]->position.x = _world.transformComponents[_idBackground[RType::GameBackground::DEFAULT]]->size.x;

	if (_world.transformComponents[_idBackground[RType::GameBackground::REVERSED]]->position.x + _world.transformComponents[_idBackground[RType::GameBackground::REVERSED]]->size.x <= 0.0f)
		_world.transformComponents[_idBackground[RType::GameBackground::REVERSED]]->position.x = _world.transformComponents[_idBackground[RType::GameBackground::REVERSED]]->size.x;
}
