#include "ComponentState.h"

namespace oct
{
	ComponentState::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts)
	:	window(&window),
		textures(&textures),
		fonts(&fonts)
	{
	}

	ComponentState::ComponentState(StateStack* stack, Context context)
	:	stack	(stack),
		context	(context)
	{
	}

	void ComponentState::requestStackPush(States::ID stateID)
	{
		stack->pushState(stateID);
	}

	void ComponentState::requestStackPop()
	{
		stack->popState();
	}

	void ComponentState::requestStateClear()
	{
		stack->clearStates();
	}

	ComponentState::Context ComponentState::getBaseContext() const
	{
		return this->context;
	}
}
