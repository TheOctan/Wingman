#include "SplashScreenState.h"

SplashScreenState::SplashScreenState(oct::StateStack* stack, Context context)
	: StateComponent(stack, context)
{
}

bool SplashScreenState::handleEvent(const sf::Event& event)
{
	return false;
}

bool SplashScreenState::update(sf::Time dt)
{
	return false;
}

void SplashScreenState::renderUpdate()
{
}
