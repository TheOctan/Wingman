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

	return true;
}

bool EditorState::postUpdate(sf::Time dt)
{
	StateComponent::postUpdate(dt);
	editor.update(dt.asSeconds());

	return true;
}

void EditorState::renderUpdate()
{
	StateComponent::renderUpdate();
	editor.draw();
}
