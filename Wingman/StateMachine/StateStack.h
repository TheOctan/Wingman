#pragma once

#include <functional>

namespace States
{
	enum ID;
}

namespace oct
{
	class StateStack
	{
	public:
		virtual ~StateStack() = default;

		virtual void foreach(std::function<void(const ActivityRef&)> operation) = 0;
		virtual bool foreach_if(std::function<bool(const ActivityRef&)> operation) = 0;

		virtual void pushState(States::ID stateID) = 0;
		virtual void popState() = 0;
		virtual void clearStates() = 0;

		virtual bool isEmpty() const = 0;
		virtual int countStates() const = 0;
	};
}