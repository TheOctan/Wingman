#pragma once

#include "StateComponent.h"
#include "GUI.hpp"

class PauseState : public oct::StateComponent
{
public:
	PauseState(oct::StateStack* stack, Context context);

	virtual void onCreate() override;

	virtual bool handleEvent(const sf::Event& event) override;

	virtual bool update(sf::Time dt) override;

	virtual void renderUpdate() override;

private:
	void onResumeBottonClick(gui::Widget* sender, const WidgetEventArgs& e);
	void onRestartBottonClick(gui::Widget* sender, const WidgetEventArgs& e);
	void onMenuBottonClick(gui::Widget* sender, const WidgetEventArgs& e);

private:
	gui::StackMenu menu;

	gui::Button* resumeButton;
	gui::Button* restartBotton;
	gui::Button* menuButton;
};

