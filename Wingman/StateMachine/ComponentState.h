#pragma once

// #include <SFML/Graphics.hpp>
#include "Object.h"
#include "State.h"
#include "Activity.h"

namespace oct
{
	class ComponentState : public Object, public Activity, public State
	{
		OCT_OBJECT(ComponentState, Object);

	public:
		ComponentState();
		virtual ~ComponentState();

		virtual void handleEvent(sf::Event event) {}

		virtual void preUpdate() {}
		virtual void update(sf::Time dt) {}
		virtual void postUpdate() {}

		virtual void renderPreUpdate() {}
		virtual void renderUpdate() {}
		virtual void renderPostUpdate() {}

		virtual void init() {}
		virtual void start() {}
		virtual void resume() {}
		virtual void pause() {}		
		virtual void stop() {}
		virtual void restart() {}
		virtual void destroy() {}
	};
}