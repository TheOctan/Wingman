#pragma once

#include "StateStack.h"
#include "StateActivity.h"
#include "ComponentState.h"
#include "Adapters/StateIdentifiers.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>

namespace sf
{
	class Event;
	class RenderWindow;
}

namespace oct
{
	class StateMachine : public StateStack<States::ID>, public StateActivity, private sf::NonCopyable
	{
	public:
		enum Action
		{
			Push,
			Pop,
			Clear,
		};

	public:
		explicit			StateMachine(ComponentState::Context context);

		template <typename T, typename... Param>
		void				registerState(States::ID stateID, Param... arg);

		bool				handleEvent(const sf::Event& event);
		
		bool				preUpdate();
		bool				update(sf::Time dt);
		bool				postUpdate();

		void				renderPreUpdate();
		void				renderUpdate();
		void				renderPostUpdate();

		void				pushState(States::ID stateID);
		void				popState();
		void				clearStates();

		bool				isempty();

	private:
		ComponentState::Ptr	createState(States::ID stateID);
		void				applyPendingChanges();

	private:
		struct PendingChange
		{
			explicit			PendingChange(Action action, States::ID stateID = States::None);

			Action				action;
			States::ID			stateID;
		};

	private:
		std::vector<ComponentState::Ptr>							mStack;
		std::vector<PendingChange>									mPendingList;

		ComponentState::Context										mContext;
		std::map<States::ID, std::function<ComponentState::Ptr()>>	mFactories;
	};

	template<typename T, typename... Param>
	inline void StateMachine::registerState(States::ID stateID, Param... arg)
	{
		mFactories[stateID] = [this, arg...]()
		{
			return ComponentState::Ptr(new T(this, mContext, arg...));
		};
	}
}

