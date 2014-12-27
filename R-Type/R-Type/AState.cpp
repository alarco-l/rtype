#include "AState.h"

AState::AState(Game *game) : _game(game)
{
}

AState::~AState()
{
}

void							AState::update(const sf::Time &elapsed)
{
	ParticleSystem::update(_world, elapsed);
	TransformSystem::update(_world, elapsed, _rfc);
	CollisionSystem::update(_world, sf::Vector2u(10, 10), _game->getScreenSize(), _rfc);
	AnimationSystem::update(_world, elapsed);
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