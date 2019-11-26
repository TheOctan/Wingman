#pragma once

namespace oct
{
	class State
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
}