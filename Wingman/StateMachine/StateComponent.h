#pragma once

// #include <SFML/Graphics.hpp>
#include "Core.h"
#include "Object.h"
#include "Resource.h"
#include "State.h"
#include "Activity.h"
#include "StateStack.h"
#include "Adapters/StateIdentifiers.h"

#include <SFML/Graphics.hpp>

namespace oct
{
	class StateComponent : public State, public Object, sf::NonCopyable
	{
		OCT_OBJECT(StateComponent, Object);

	public:
		StateComponent(StateStack* stack, Context context);
		virtual ~StateComponent() = default;

		virtual void onCreate() {}
		virtual void onStart() {}
		virtual void onResume() {}
		virtual void onPause() {}
		virtual void onStop() {}
		virtual void onRestart() {}
		virtual void onDestroy() {}

		virtual bool handleEvent(const sf::Event& event) { return false; }

		virtual bool preUpdate(sf::Time dt) { return false; }
		virtual bool update(sf::Time dt) { return false; }
		virtual bool postUpdate(sf::Time dt) { return false; }

		virtual void renderPreUpdate() {}
		virtual void renderUpdate() {}
		virtual void renderPostUpdate() {}

	protected:
		void requestStackPush(States::ID stateID);
		void requestStackPop();
		void requestStateClear();

		Context getBaseContext() const;

	private:
		StateStack*		stack;
		Context			context;
	};

	using StateComponentRef = Ref<StateComponent>;
}