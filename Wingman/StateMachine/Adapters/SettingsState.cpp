#include "SettingsState.h"

#include <iostream>

SettingsState::SettingsState(oct::StateStack* stack, Context context)
	: StateComponent(stack, context),
	settings(getBaseContext().configuration)
{
}

void SettingsState::onCreate()
{
	const auto& font = getBaseContext().fonts->get(Fonts::Main);

	musicBar = new gui::ScrollBar("Music");
	musicBar->setFont(font);
	musicBar->subscribe(this, &SettingsState::onMusicBarChange);
	musicBar->setValue(settings->music);

	soundBar = new gui::ScrollBar("Sound");
	soundBar->setFont(font);
	soundBar->subscribe(this, &SettingsState::onSoundBarChange);
	soundBar->setValue(settings->sound);

	fullScreenLock = new gui::Lock("Full screen mode");
	fullScreenLock->setFont(font);
	fullScreenLock->subscribe(this, &SettingsState::onFullScreenLockChange);
	fullScreenLock->isLocked = settings->fullScreen;

	secondPlayerLock = new gui::Lock("Add second player");
	secondPlayerLock->setFont(font);
	secondPlayerLock->subscribe(this, &SettingsState::onSecondPlayerLockChange);
	secondPlayerLock->isLocked = settings->secondPlayer;

	thirdPlayerLock = new gui::Lock("Add third player");
	thirdPlayerLock->setFont(font);
	thirdPlayerLock->subscribe(this, &SettingsState::onThirdPlayerLockChange);
	thirdPlayerLock->isLocked = settings->thirdPlayer;

	resetButton = new gui::Button("Reset");
	resetButton->setFont(font);
	resetButton->subscribe(this, &SettingsState::onResetButtonClick);

	backButton = new gui::Button("Back");
	backButton->setFont(font);
	backButton->subscribe(this, &SettingsState::onBackButtonClick);

	menu.setTitle("Settings");
	menu.setFont(font);
	menu.setFillColor(sf::Color(255, 255, 255, 150));
	menu.setOutlineColor(sf::Color::Transparent);

	menu.addWidget(musicBar);
	menu.addWidget(soundBar);

	menu.addWidget(fullScreenLock);
	menu.addWidget(secondPlayerLock);
	menu.addWidget(thirdPlayerLock);

	menu.addWidget(resetButton);
	menu.addWidget(backButton);

	menu.setOrigin(menu.getSize() / 2.f);
	menu.setPosition(sf::Vector2f(getBaseContext().window->getSize()) / 2.f);
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	StateComponent::handleEvent(event);

	menu.handleEvent(event);

	return false;
}

bool SettingsState::update(sf::Time dt)
{
	return StateComponent::update(dt);
}

void SettingsState::renderUpdate()
{
	StateComponent::renderUpdate();

	getBaseContext().window->draw(menu);
}

void SettingsState::onMusicBarChange(gui::Widget* sender, const WidgetEventArgs& e)
{
	settings->music = e.value;
	std::cout << settings->music << std::endl;
}

void SettingsState::onSoundBarChange(gui::Widget* sender, const WidgetEventArgs& e)
{
	settings->sound = e.value;
}

void SettingsState::onFullScreenLockChange(gui::Widget* sender, const WidgetEventArgs& e)
{
	settings->fullScreen = e.value;
}

void SettingsState::onSecondPlayerLockChange(gui::Widget* sender, const WidgetEventArgs& e)
{
	settings->secondPlayer = e.value;
}

void SettingsState::onThirdPlayerLockChange(gui::Widget* sender, const WidgetEventArgs& e)
{
	settings->thirdPlayer = e.value;
}

void SettingsState::onResetButtonClick(gui::Widget* sender, const WidgetEventArgs& e)
{
	musicBar->setValue(100);
	soundBar->setValue(100);

	fullScreenLock->isLocked = false;
	secondPlayerLock->isLocked = false;
	thirdPlayerLock->isLocked = false;

	settings->music = 100;
	settings->sound = 100;
	
	settings->fullScreen = false;
	settings->secondPlayer = false;
	settings->thirdPlayer = false;
}

void SettingsState::onBackButtonClick(gui::Widget* sender, const WidgetEventArgs& e)
{
	requestStackPop();
	requestStackPush(States::MainMenu);
}
