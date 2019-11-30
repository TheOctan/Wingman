#pragma once

#include "Activity.h"
#include "StateMachine.h"

namespace oct
{
	class ActivityManager : public Activity
	{
	public:
		bool handleEvent(const sf::Event& event);

		bool preUpdate();
		bool update(sf::Time dt);
		bool postUpdate();

		void renderPreUpdate();
		void renderUpdate();
		void renderPostUpdate();


	private:
		StateMachine* machine;
	};
}
