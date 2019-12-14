#include "EditorState.h"

EditorState::EditorState(oct::StateStack* stack, Context context)
	: StateComponent(stack, context),
	game(getBaseContext().window),
	editor(getBaseContext().window)
{
}

bool EditorState::handleEvent(const sf::Event& event)
{
	StateComponent::handleEvent(event);

	if(event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape)
		{
			requestStackPop();
			requestStackPush(States::Game);
			requestStackPush(States::MainMenu);
		}

	return false;
}

bool EditorState::postUpdate(sf::Time dt)
{
	StateComponent::postUpdate(dt);
	editor.update(dt.asSeconds());

	return false;
}

void EditorState::renderUpdate()
{
	StateComponent::renderUpdate();
	editor.draw();
}
