#pragma once

#include "StateComponent.h"

namespace oct
{
	class ConcreteState : public StateComponent
	{
	public:
		ConcreteState(StateStack* stack, Context context);


	};
}