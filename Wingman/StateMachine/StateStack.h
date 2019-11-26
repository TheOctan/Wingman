#pragma once

namespace oct
{
	template <class Identificator>
	class StateStack
	{
	public:
		virtual ~StateStack() = default;

		virtual void pushState(Identificator stateID) = 0;
		virtual void popState() = 0;
		virtual void clearStates() = 0;

		virtual bool isempty() = 0;
	};
}