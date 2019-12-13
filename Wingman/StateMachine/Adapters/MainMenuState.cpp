#include "MainMenuState.h"

std::string MainMenuState::fontPath = "Fonts/Dosis-Light.ttf";

MainMenuState::MainMenuState(oct::StateStack* stack, Context context)
	: StateComponent(stack, context),
	game(getBaseContext().window)
{
}

void MainMenuState::onCreate()
{
	const auto& font = getBaseContext().fonts->get(Fonts::Main);

	startButton = new gui::Button("Start game");
	startButton->setFont(font);
	startButton->subscribe(this, &MainMenuState::onStartButtonClick);

	editButton = new gui::Button("Editor");
	editButton->setFont(font);
	editButton->subscribe(this, &MainMenuState::onEditButtonClick);

	settingsButton = new gui::Button("Settings");
	settingsButton->setFont(font);
	settingsButton->subscribe(this, &MainMenuState::onSettingsButtonClick);

	exitButton = new gui::Button("Exit");
	exitButton->setFont(font);
	exitButton->subscribe(this, &MainMenuState::onExitButtonClick);

	menu.setFont(font);
	menu.setTitle("Main menu");
	menu.setFillColor(sf::Color(255, 255, 255, 150));

	menu.addWidget(startButton);
	menu.addWidget(editButton);
	menu.addWidget(settingsButton);
	menu.addWidget(exitButton);

	menu.setOrigin(menu.getSize() / 2.f);
	menu.setPosition(sf::Vector2f(getBaseContext().window->getSize()) / 2.f);
}

bool MainMenuState::handleEvent(const sf::Event& event)
{
	StateComponent::handleEvent(event);

	menu.handleEvent(event);

	if (event.type == sf::Event::Resized)
	{
		menu.setPosition(sf::Vector2f(getBaseContext().window->getSize()) / 2.f);
	}

	return false;
}

bool MainMenuState::update(sf::Time dt)
{
	StateComponent::update(dt);

	return false;
}

bool MainMenuState::postUpdate(sf::Time dt)
{
	StateComponent::postUpdate(dt);

	return false;
}

void MainMenuState::renderUpdate()
{
	StateComponent::renderUpdate();

	game.draw();
	getBaseContext().window->draw(menu);
}

void MainMenuState::onStartButtonClick(gui::Widget* sender, const WidgetEventArgs& e)
{

}

void MainMenuState::onEditButtonClick(gui::Widget* sender, const WidgetEventArgs& e)
{

}

void MainMenuState::onSettingsButtonClick(gui::Widget* sender, const WidgetEventArgs& e)
{

}

void MainMenuState::onExitButtonClick(gui::Widget* sender, const WidgetEventArgs& e)
{
	requestStateClear();
}
