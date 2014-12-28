#include "AState.h"

AState::AState(Game *game) : _game(game), _rfc(NULL)
{
}

AState::~AState()
{
}

void							AState::update(const sf::Time &elapsed)
{
	TimerSystem::update(_world, elapsed);
	WeaponSystem::update(_world, elapsed, _game->factory, _game->getScreenSize());
	ParticleSystem::update(_world, elapsed);
	TransformSystem::update(_world, elapsed, _game->getScreenSize());
	CollisionSystem::update(_world, sf::Vector2u(10, 10), _game->getScreenSize());
	HealthSystem::update(_world, elapsed, _game->factory);
	AnimationSystem::update(_world, elapsed);
	DeathSystem::update(_world);
}

void							AState::draw(sf::RenderWindow *window)
{
	RenderSystem::update(window, _world);
	TextSystem::update(window, _world);
}

bool							AState::isBlocking() const
{
	return (_isBlocking);
}