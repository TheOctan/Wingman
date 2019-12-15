#pragma once

#include "Core.h"
#include "Activity.h"

namespace oct
{
	class State : public Activity
	{
	public:
		virtual ~State() = default;

		virtual void onCreate()		= 0;
		virtual void onStart()		= 0;
		virtual void onResume()		= 0;
		virtual void onPause()		= 0;
		virtual void onStop()		= 0;
		virtual void onRestart()	= 0;
		virtual void onDestroy()	= 0;
	};

	using StateRef = Ref<State>;
}