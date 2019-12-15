#include "GameState.h"

GameState::GameState(oct::StateStack* stack, Context context)
	: StateComponent(stack, context),
	game(getBaseContext().window)
{
	auto settings = getBaseContext().configuration;

	if (settings->secondPlayer)
		game.addPlayer(Game::secondPlayer);

	if (settings->thirdPlayer)
		game.addPlayer(Game::thirdPlayer);
}

bool GameState::handleEvent(const sf::Event& event)
{
	StateComponent::handleEvent(event);

	if(event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape)
		{
			requestStackPush(States::PauseMenu);
		}

	return false;
}

bool GameState::postUpdate(sf::Time dt)
{
	StateComponent::postUpdate(dt);
	game.update(dt.asSeconds());

	return false;
}

void GameState::renderUpdate()
{
	StateComponent::renderUpdate();
	game.draw();
}
