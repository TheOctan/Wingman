#pragma once

namespace oct
{
	class State
	{
	public:
		virtual ~State() = default;

		virtual void init()		= 0;
		virtual void start()	= 0;
		virtual void resume()	= 0;
		virtual void pause()	= 0;
		virtual void stop()		= 0;
		virtual void restart()	= 0;
		virtual void destroy()	= 0;
	};
}