#pragma once

#include "StateComponent.h"
#include "GUI.hpp"

class SettingsState : public oct::StateComponent
{
public:
	SettingsState(oct::StateStack* stack, Context context);

	virtual void onCreate() override;

	virtual bool handleEvent(const sf::Event& event) override;

	virtual bool update(sf::Time dt) override;

	virtual void renderUpdate() override;

private:
	void onMusicBarChange(gui::Widget* sender, const WidgetEventArgs& e);
	void onSoundBarChange(gui::Widget* sender, const WidgetEventArgs& e);

	void onFullScreenLockChange(gui::Widget* sender, const WidgetEventArgs& e);
	void onSecondPlayerLockChange(gui::Widget* sender, const WidgetEventArgs& e);
	void onThirdPlayerLockChange(gui::Widget* sender, const WidgetEventArgs& e);

	void onResetButtonClick(gui::Widget* sender, const WidgetEventArgs& e);
	void onBackButtonClick(gui::Widget* sender, const WidgetEventArgs& e);

private:
	gui::StackMenu	menu;

	gui::ScrollBar* musicBar;
	gui::ScrollBar* soundBar;

	gui::Lock*		fullScreenLock;
	gui::Lock*		secondPlayerLock;
	gui::Lock*		thirdPlayerLock;

	gui::Button*	resetButton;
	gui::Button*	backButton;

	Settings*		settings;
};

