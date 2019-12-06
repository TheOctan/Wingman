#pragma once

namespace States
{
	enum ID
	{
		None,			// 
		Load,			// 
		MainMenu,		// 
		Game,			// Game state contains gameplay
		Editor,			// Editor allows to edit levels
		Test,			// Concrete state fot example
		StatesCount		// 
	};
}
