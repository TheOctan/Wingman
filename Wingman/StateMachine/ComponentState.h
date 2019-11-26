#pragma once

// #include <SFML/Graphics.hpp>
#include "Object.h"
#include "State.h"
#include "StateActivity.h"
#include "StateStack.h"
#include "Adapters/StateIdentifiers.h"

#include <memory>

namespace oct
{
	class ComponentState : public Object, public StateActivity, public State
	{
		OCT_OBJECT(ComponentState, Object);

	public:
		typedef std::unique_ptr<ComponentState> Ptr;
		typedef StateStack<States::ID>	StateStack;

		struct Context
		{
			Context(sf::RenderWindow& window);

			sf::RenderWindow* window;
		};

	public:
		ComponentState(StateStack* stack, Context context);
		virtual ~ComponentState() = default;

		virtual bool handleEvent(const sf::Event& event) {}

		virtual bool preUpdate() {}
		virtual bool update(sf::Time dt) {}
		virtual bool postUpdate() {}

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

	protected:
		void requestStackPush(States::ID stateID);
		void requestStackPop();
		void requestStateClear();

		Context getBaseContext() const;

	private:
		StateStack*		stack;
		Context			context;
	};
}