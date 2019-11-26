#pragma once

#include <SFML/Graphics.hpp>

namespace oct
{
	class StateActivity
	{
	public:
		virtual ~StateActivity() = default;

		virtual bool handleEvent(const sf::Event& event) = 0;

		virtual bool preUpdate()			= 0;
		virtual bool update(sf::Time dt)	= 0;
		virtual bool postUpdate()			= 0;

		virtual void renderPreUpdate()		= 0;
		virtual void renderUpdate()			= 0;
		virtual void renderPostUpdate()		= 0;
	};
}