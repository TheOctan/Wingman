#pragma once

#include "Core.h"
#include "Activity.h"
#include "StateMachine.h"
#include "StateComponent.h"

namespace oct
{
	class ActivityManager : public Activity
	{
	public:
		ActivityManager(Activity::Context context)
		{
			machine = std::make_unique<StateMachine>(context);
			registerStates();
		}

		bool handleEvent(const sf::Event& event);

		bool preUpdate();
		bool update(sf::Time dt);
		bool postUpdate();

		void renderPreUpdate();
		void renderUpdate();
		void renderPostUpdate();

	protected:
		virtual void registerStates() const;

	private:
		Scope<StateMachine> machine;
	};
}
