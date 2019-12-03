#pragma once

#include "StateComponent.h"


class ConcreteState : public oct::StateComponent
{
public:
	ConcreteState(oct::StateStack* stack, Context context);


};