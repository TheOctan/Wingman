#include "StateMachine.h"

#include <cassert>

namespace oct
{
	StateMachine::StateMachine(ComponentState::Context context)
	:	mStack		(),
		mFactories	(),
		mPendingList(),
		mContext	(context)
	{
	}

	bool StateMachine::handleEvent(const sf::Event& event)
	{
		// Iterate from top to bottom, stop as soon as handleEvent() returns false
		for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
		{
			if (!(*itr)->handleEvent(event))
				break;
		}
		applyPendingChanges();

		return true;
	}

	bool StateMachine::preUpdate()
	{
		return true;
	}

	bool StateMachine::update(sf::Time dt)
	{
		// Iterate from top to bottom, stop as soon as update() returns false
		for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
		{
			if (!(*itr)->update(dt))
				break;
		}
		applyPendingChanges();

		return true;
	}

	bool StateMachine::postUpdate()
	{
		return true;
	}

	void StateMachine::renderPreUpdate()
	{
	}

	void StateMachine::renderUpdate()
	{
		// Draw all active states from bottom to top
		for (ComponentState::Ptr& state : mStack)
			state->renderUpdate();
	}

	void StateMachine::renderPostUpdate()
	{
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

	bool StateMachine::isempty()
	{
		return mStack.empty();
	}

	ComponentState::Ptr StateMachine::createState(States::ID stateID)
	{
		auto found = mFactories.find(stateID);
		assert(found != mFactories.end());

		return found->second();
	}

	void StateMachine::applyPendingChanges()
	{
		for (PendingChange change : mPendingList)
		{
			switch (change.action)
			{
			case Push:
				mStack.push_back(createState(change.stateID));
				break;

			case Pop:
				mStack.back()->onDestroy();
				mStack.pop_back();

				if (!mStack.empty())
					mStack.back()->onResume();
				break;

			case Clear:
				for (ComponentState::Ptr& state : mStack)
					state->onDestroy();

				mStack.clear();
				break;
			}
		}

		mPendingList.clear();
	}

	StateMachine::PendingChange::PendingChange(Action action, States::ID stateID)
	:	action	(action),
		stateID	(stateID)
	{
	}
}