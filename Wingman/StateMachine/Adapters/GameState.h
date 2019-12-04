#pragma once

#include "StateComponent.h"
#include "Game.h"

class GameState : public oct::StateComponent
{
public:
	GameState(oct::StateStack* stack, Context context);

	virtual bool handleEvent(const sf::Event& event) override;

	virtual bool update(sf::Time dt) override;

	virtual void renderUpdate() override;

private:
	Game game;
};

