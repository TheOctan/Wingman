#pragma once

#include "Resource.h"
#include "Activity.h"
#include "ActivityManager.h"
#include "StateMachine.h"
#include "Resource/ResourceIdentifiers.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Application
{
public:
	Application();

	void run();

private:
	void					processInput();
	void					preUpdate(sf::Time dt);
	void					update(sf::Time dt);
	void					postUpdate(sf::Time dt);
	void					render();

	void					updateStatistics(sf::Time dt);
	void					registerStates();

protected:
	oct::Activity::Context getBaseContext();

protected:
	oct::ActivityManager	activity;
	oct::StateMachine		machine;

private:
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		mWindow;
	TextureHolder			mTextures;
	FontHolder				mFonts;

	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;
	std::size_t				mStatisticsNumFrames;
};

