#include "GameState.h"

GameState::GameState(oct::StateStack* stack, Context context)
	: StateComponent(stack, context),
	game(getBaseContext().window)
{
}

bool GameState::handleEvent(const sf::Event& event)
{
	StateComponent::handleEvent(event);

	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
		requestStateClear();

	return true;
}

bool GameState::update(sf::Time dt)
{
	StateComponent::update(dt);
	game.update(dt.asSeconds());

	return true;
}

void GameState::renderUpdate()
{
	StateComponent::renderUpdate();
	game.draw();
}
