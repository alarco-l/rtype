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
	TransformSystem::update(_world, elapsed);
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