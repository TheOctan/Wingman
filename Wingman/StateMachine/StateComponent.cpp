#include "StateComponent.h"

namespace oct
{
	Activity::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts)
	:	window	(&window),
		textures(&textures),
		fonts	(&fonts)
	{
	}

	StateComponent::StateComponent(StateStack* stack, Context context)
	:	stack	(stack),
		context	(context)
	{
	}

	void StateComponent::requestStackPush(States::ID stateID)
	{
		stack->pushState(stateID);
	}

	void StateComponent::requestStackPop()
	{
		stack->popState();
	}

	void StateComponent::requestStateClear()
	{
		stack->clearStates();
	}

	Activity::Context StateComponent::getBaseContext() const
	{
		return this->context;
	}
}
