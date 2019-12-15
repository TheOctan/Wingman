#pragma once

#include "Core.h"
#include "Activity.h"
#include "StateStack.h"
#include "StateComponent.h"
#include "Adapters/StateIdentifiers.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <map>

namespace sf
{
	class Event;
	class RenderWindow;
}

namespace oct
{
	class StateMachine : public StateStack, private sf::NonCopyable
	{
	public:
		enum Action
		{
			Push,
			Pop,
			Clear
		};

	public:
		explicit			StateMachine(Activity::Context context);

		template <typename T, typename... Param>
		void				registerState(States::ID stateID, Param&&... arg);
		void				foreach(std::function<void(const ActivityRef&)> operation);
		bool				foreach_if(std::function<bool(const ActivityRef&)> operation);

		void				pushState(States::ID stateID);
		void				popState();
		void				clearStates();

		bool				isEmpty() const;
		int					countStates() const;

	private:
		StateRef			createState(States::ID stateID);
		bool				applyPendingChanges();

	private:
		struct PendingChange
		{
			explicit			PendingChange(Action action, States::ID stateID = States::None);

			Action				action;
			States::ID			stateID;
		};

	private:
		std::vector<StateRef>								mStack;
		std::vector<PendingChange>							mPendingList;

		Activity::Context								mContext;
		std::map<States::ID, std::function<StateRef()>>	mFactories;
	};

}

#include "StateMachine.inl"
