#pragma once

// #include <SFML/Graphics.hpp>
#include "Object.h"
#include "State.h"
#include "StateActivity.h"
#include "StateStack.h"
#include "Adapters/StateIdentifiers.h"
#include "Resource/ResourceIdentifiers.h"

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
			Context(
				sf::RenderWindow&	window,
				TextureHolder&		textures,
				FontHolder&			fonts);

			sf::RenderWindow*	window;
			TextureHolder*		textures;
			FontHolder*			fonts;
		};

	public:
		ComponentState(StateStack* stack, Context context);
		virtual ~ComponentState() = default;

		virtual bool handleEvent(const sf::Event& event) { return true; }

		virtual bool preUpdate() { return true; }
		virtual bool update(sf::Time dt) { return true; }
		virtual bool postUpdate() { return true; }

		virtual void renderPreUpdate() {}
		virtual void renderUpdate() {}
		virtual void renderPostUpdate() {}

		virtual void onCreate() {}
		virtual void onStart() {}
		virtual void onResume() {}
		virtual void onPause() {}
		virtual void onStop() {}
		virtual void onRestart() {}
		virtual void onDestroy() {}

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