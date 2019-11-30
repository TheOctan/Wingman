#pragma once

#include "Core.h"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

namespace oct
{
	class Activity
	{
	public:
		virtual ~Activity() = default;

		virtual bool handleEvent(const sf::Event& event) = 0;

		virtual bool preUpdate()			= 0;
		virtual bool update(sf::Time dt)	= 0;
		virtual bool postUpdate()			= 0;

		virtual void renderPreUpdate()		= 0;
		virtual void renderUpdate()			= 0;
		virtual void renderPostUpdate()		= 0;
	};

	using ActivityRef = Ref<Activity>;
}