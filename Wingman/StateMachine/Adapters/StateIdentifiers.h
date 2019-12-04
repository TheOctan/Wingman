#pragma once

namespace States
{
	enum ID
	{
		None,			// 
		Load,			// 
		MainMenu,		// 
		Game,			// Game state contains gameplay
		Editor,			// 
		Test,			// Concrete state fot example
		StatesCount		// 
	};
}
