#include "Application.h"
#include "StateAdapter.h"

#include <string>

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
	: mWindow(sf::VideoMode(1920, 1080), "Wingman Game", sf::Style::Default),
	mTextures(),
	mFonts(),
	machine(getBaseContext()),
	activity(machine),
	mStatisticsText(),
	mStatisticsUpdateTime(),
	mStatisticsNumFrames(0)
{
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setVerticalSyncEnabled(true);

	mFonts.load(Fonts::Main, "Fonts/Dosis-Light.ttf");

	mStatisticsText.setFont(mFonts.get(Fonts::Main));
	mStatisticsText.setPosition(mWindow.getSize().x - mStatisticsText.getGlobalBounds().width - 200.f, 50.f);
	mStatisticsText.setCharacterSize(30u);

	registerStates();
	machine.pushState(States::Game);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();

		if (dt > sf::seconds(0.25f))
			dt = sf::seconds(0.25f);

		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);

			// Check inside this loop, because stack might be empty before update() call
			if (machine.isEmpty())
				mWindow.close();
		}

		updateStatistics(dt);
		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		activity.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();

		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			mWindow.close();
	}
}

void Application::update(sf::Time dt)
{
	activity.update(dt);
}

void Application::render()
{
	mWindow.clear();

	activity.renderUpdate();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);

	mWindow.display();
}

void Application::updateStatistics(sf::Time dt)
{
	mStatisticsUpdateTime += dt;
	mStatisticsNumFrames += 1;
	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString("FPS: " + std::to_string(mStatisticsNumFrames) + "\nCount states: " + std::to_string(machine.countStates()));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Application::registerStates()
{
	machine.registerState<ConcreteState>(States::Test);
	machine.registerState<GameState>(States::Game);
	machine.registerState<EditorState>(States::Editor);
}

oct::Activity::Context Application::getBaseContext()
{
	return oct::Activity::Context(mWindow, mTextures, mFonts);
}
