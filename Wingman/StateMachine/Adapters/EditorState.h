#pragma once

#include "StateComponent.h"
#include "GameMapMaker.h"

class EditorState : public oct::StateComponent
{
public:
	EditorState(oct::StateStack* stack, Context context);

	virtual bool handleEvent(const sf::Event& event) override;

	virtual bool update(sf::Time dt) override;

	virtual void renderUpdate() override;

private:
	GameMapMaker editor;
};

