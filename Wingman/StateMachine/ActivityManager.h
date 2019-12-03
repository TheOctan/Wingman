#pragma once

#include "Activity.h"
#include "StateStack.h"

namespace oct
{
	class ActivityManager : public Activity
	{
	public:
		ActivityManager(StateStack& stack);

		bool handleEvent(const sf::Event& event);

		bool preUpdate();
		bool update(sf::Time dt);
		bool postUpdate();

		void renderPreUpdate();
		void renderUpdate();
		void renderPostUpdate();

	protected:
		//virtual void registerStates();

	private:
		StateStack* stateStack;
	};
}
