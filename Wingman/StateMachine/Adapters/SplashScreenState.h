#pragma once

#include "StateComponent.h"

class SplashScreenState : public oct::StateComponent
{
public:
	SplashScreenState(oct::StateStack* stack, Context context);

	virtual bool handleEvent(const sf::Event& event) override;

	virtual bool update(sf::Time dt) override;

	virtual void renderUpdate() override;

private:
};

