#pragma once

namespace States
{
	enum ID
	{
		None,			// 
		Load,			// Loading screen
		Background,		// Interactive background for application
		MainMenu,		// Start point of game for simple user
		PauseMenu,		// State for pause of game
		Game,			// Game state contains gameplay
		GameOver,		// End the game
		Editor,			// Editor allows to edit levels
		Settings,		// Settings menu of game
		SplashScreen,	// First screen of launched application
		Test,			// Concrete state fot example
		StatesCount		// Count of all states
	};
}
