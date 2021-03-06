#include "StateMachine.h"

#include <cassert>

namespace oct
{
	StateMachine::StateMachine(Activity::Context context)
	:	mStack		(),
		mFactories	(),
		mPendingList(),
		mContext	(context)
	{
	}

	void StateMachine::foreach(std::function<void(const ActivityRef&)> operation)
	{
		for (auto& state : mStack)
			operation(state);
	}

	bool StateMachine::foreach_if(std::function<bool(const ActivityRef&)> operation)
	{
		// Iterate from top to bottom, stop as soon as operation() returns false
		for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
		{
			const auto& state = *itr;

			if (!operation(state))
				break;
		}

		return applyPendingChanges();
	}

	void StateMachine::pushState(States::ID stateID)
	{
		mPendingList.push_back(PendingChange(Push, stateID));
	}

	void StateMachine::popState()
	{
		mPendingList.push_back(PendingChange(Pop));
	}

	void StateMachine::clearStates()
	{
		mPendingList.push_back(PendingChange(Clear));
	}

	bool StateMachine::isEmpty() const
	{
		return mStack.empty();
	}

	int StateMachine::countStates() const
	{
		return mStack.size();
	}

	StateRef StateMachine::createState(States::ID stateID)
	{
		auto found = mFactories.find(stateID);
		assert(found != mFactories.end());

		return found->second();
	}

	bool StateMachine::applyPendingChanges()
	{
		for (PendingChange change : mPendingList)
		{
			switch (change.action)
			{
			case Push:
			{
				const auto& state = createState(change.stateID);
				state->onCreate();

				mStack.push_back(state);
				break;
			}
			case Pop:
				mStack.back()->onDestroy();
				mStack.pop_back();

				if (!mStack.empty())
					mStack.back()->onResume();
				break;

			case Clear:
				for (StateRef& state : mStack)
					state->onDestroy();

				mStack.clear();
				break;
			}
		}

		mPendingList.clear();

		return true;
	}

	StateMachine::PendingChange::PendingChange(Action action, States::ID stateID)
	:	action	(action),
		stateID	(stateID)
	{
	}
}