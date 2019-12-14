#include "PauseState.h"
#include "Player.h"

PauseState::PauseState(oct::StateStack* stack, Context context)
	: StateComponent(stack, context)
{
}

void PauseState::onCreate()
{
	const auto& font = getBaseContext().fonts->get(Fonts::Main);

	resumeButton = new gui::Button("Resume");
	resumeButton->setFont(font);
	resumeButton->subscribe(this, &PauseState::onResumeBottonClick);

	restartBotton = new gui::Button("Restart");
	restartBotton->setFont(font);
	restartBotton->subscribe(this, &PauseState::onRestartBottonClick);

	menuButton = new gui::Button("To menu");
	menuButton->setFont(font);
	menuButton->subscribe(this, &PauseState::onMenuBottonClick);

	menu.setFillColor(sf::Color(255, 255, 255, 150));
	menu.setOutlineColor(sf::Color::Transparent);

	menu.addWidget(resumeButton);
	menu.addWidget(restartBotton);
	menu.addWidget(menuButton);

	menu.setOrigin(menu.getSize() / 2.f);
	menu.setPosition(sf::Vector2f(getBaseContext().window->getSize()) / 2.f);
}

bool PauseState::handleEvent(const sf::Event& event)
{
	StateComponent::handleEvent(event);

	if(event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape)
		{
			requestStackPop();
		}

	menu.handleEvent(event);

	return false;
}

bool PauseState::update(sf::Time dt)
{
	return StateComponent::update(dt);
}

void PauseState::renderUpdate()
{
	StateComponent::renderUpdate();

	getBaseContext().window->draw(menu);
}

void PauseState::onResumeBottonClick(gui::Widget* sender, const WidgetEventArgs& e)
{
	requestStackPop();
}

void PauseState::onRestartBottonClick(gui::Widget* sender, const WidgetEventArgs& e)
{
	requestStateClear();
	requestStackPush(States::Game);
	Player::players = 0;
}

void PauseState::onMenuBottonClick(gui::Widget* sender, const WidgetEventArgs& e)
{
	requestStackPop();
	requestStackPush(States::MainMenu);
}
