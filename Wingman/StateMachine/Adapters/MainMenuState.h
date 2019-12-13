#pragma once

#include <string>

#include "StateComponent.h"
#include "GUI.hpp"

class MainMenuState : public oct::StateComponent
{
public:
	static std::string fontPath;

public:
	MainMenuState(oct::StateStack* stack, Context context);

	virtual void onCreate() override;

	virtual bool handleEvent(const sf::Event& event) override;

	virtual bool update(sf::Time dt) override;

	virtual void renderUpdate() override;

private:
	void onStartButtonClick		(gui::Widget* sender, const WidgetEventArgs& e);
	void onEditButtonClick		(gui::Widget* sender, const WidgetEventArgs& e);
	void onSettingsButtonClick	(gui::Widget* sender, const WidgetEventArgs& e);
	void onExitButtonClick		(gui::Widget* sender, const WidgetEventArgs& e);

private:
	gui::StackMenu menu;

	gui::Button* startButton;
	gui::Button* editButton;
	gui::Button* settingsButton;
	gui::Button* exitButton;
};

