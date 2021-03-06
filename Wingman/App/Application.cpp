#include "Application.h"
#include "StateAdapter.h"

#include <string>

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);
const std::string Application::appName = "Wingman";
const int Application::winWidth = 1920;
const int Application::winHeight = 1080;

Application::Application()
	: mWindow(sf::VideoMode(winWidth, winHeight), appName, sf::Style::Close),
	mTextures(),
	mFonts(),
	machine(getBaseContext()),
	activity(machine),
	mStatisticsText(),
	mStatisticsUpdateTime(),
	mStatisticsNumFrames(0)
{
	mWindow.setKeyRepeatEnabled(false);

	mFonts.load(Fonts::Main, "Fonts/Dosis-Light.ttf");
	mStatisticsText.setFont(mFonts.get(Fonts::Main));
	mStatisticsText.setCharacterSize(30u);

	registerStates();
	machine.pushState(States::Game);
	machine.pushState(States::MainMenu);
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

		preUpdate(dt);
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
		postUpdate(dt);

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

		if (event.type == Event::Resized)
			mWindow.setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
	}
}

void Application::preUpdate(sf::Time dt)
{
	activity.preUpdate(dt);
}

void Application::update(sf::Time dt)
{
	activity.update(dt);
}

void Application::postUpdate(sf::Time dt)
{
	activity.postUpdate(dt);
}

void Application::render()
{
	mWindow.clear();

	activity.renderUpdate();
	mWindow.draw(mStatisticsText);

	mWindow.display();
}

void Application::updateStatistics(sf::Time dt)
{
	mStatisticsText.setPosition(mWindow.getSize().x - mStatisticsText.getGlobalBounds().width - 50.f, 50.f);

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
	machine.registerState<MainMenuState>(States::MainMenu);
	machine.registerState<SettingsState>(States::Settings);
	machine.registerState<PauseState>(States::PauseMenu);
}

oct::Activity::Context Application::getBaseContext()
{
	return oct::Activity::Context(mWindow, mTextures, mFonts, mConfiguration);
}
