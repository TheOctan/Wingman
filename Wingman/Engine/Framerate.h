#pragma once

#include "types.h"

namespace oct
{
	struct Framerate
	{
		double time_step = (1.0 / 60.0);
		uint32 max_steps = 10;
		uint32 fps = 0;
	};
}