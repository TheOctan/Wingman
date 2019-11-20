#pragma once

#include <SFML/Graphics.hpp>

namespace oct
{
	class Activity
	{
	public:
		virtual ~Activity() = default;

		virtual void handleEvent(sf::Event event) = 0;

		virtual void preUpdate()			= 0;
		virtual void update(sf::Time dt)	= 0;
		virtual void postUpdate()			= 0;

		virtual void renderPreUpdate()		= 0;
		virtual void renderUpdate()			= 0;
		virtual void renderPostUpdate()		= 0;
	};
}