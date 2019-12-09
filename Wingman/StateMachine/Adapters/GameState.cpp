#include "GameState.h"

GameState::GameState(oct::StateStack* stack, Context context)
	: StateComponent(stack, context),
	game(getBaseContext().window)
{
}

bool GameState::handleEvent(const sf::Event& event)
{
	StateComponent::handleEvent(event);

	return true;
}

bool GameState::postUpdate(sf::Time dt)
{
	StateComponent::postUpdate(dt);
	game.update(dt.asSeconds());

	return true;
}

void GameState::renderUpdate()
{
	StateComponent::renderUpdate();
	game.draw();
}
