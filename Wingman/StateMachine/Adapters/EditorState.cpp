#include "EditorState.h"

EditorState::EditorState(oct::StateStack* stack, Context context)
	: StateComponent(stack, context),
	editor(getBaseContext().window)
{
}

bool EditorState::handleEvent(const sf::Event& event)
{
	StateComponent::handleEvent(event);

	return true;
}

bool EditorState::update(sf::Time dt)
{
	StateComponent::update(dt);
	editor.update(dt.asSeconds());

	return true;
}

void EditorState::renderUpdate()
{
	StateComponent::renderUpdate();
	editor.draw();
}
