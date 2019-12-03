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
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10u);

	registerStates();
	machine.pushState(States::Test);
}

void Application::run()
{

}

void Application::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		activity.handleEvent(event);

		if (event.type == sf::Event::Closed)
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
		mStatisticsText.setString("FPS: " + std::to_string(mStatisticsNumFrames));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Application::registerStates()
{
	machine.registerState<ConcreteState>(States::Test);
}

oct::Activity::Context Application::getBaseContext()
{
	return oct::Activity::Context(mWindow, mTextures, mFonts);
}
