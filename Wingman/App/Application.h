#pragma once

#include "Resource.h"
#include "Activity.h"
#include "ActivityManager.h"
#include "StateMachine.h"
#include "Resource.h"
#include "Settings.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

class Application
{
public:
	static const std::string appName;
	static const int winHeight;
	static const int winWidth;

	Application();

	void run();

protected:
	oct::Activity::Context getBaseContext();

private:
	void					processInput();
	void					preUpdate(sf::Time dt);
	void					update(sf::Time dt);
	void					postUpdate(sf::Time dt);
	void					render();

	void					updateStatistics(sf::Time dt);
	void					registerStates();

protected:
	oct::ActivityManager	activity;
	oct::StateMachine		machine;
	
private:
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		mWindow;
	TextureHolder			mTextures;
	FontHolder				mFonts;
	Settings				mConfiguration;

	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;
	std::size_t				mStatisticsNumFrames;
};

