#include <iostream>

#include "Application.h"

#include "Game.h"
#include "GameMapMaker.h"

bool MAPMAKER = true;
#define GAME_ENGINE_APPLICATION

int main()
{
	srand(time(NULL));


#ifdef GAME_ENGINE_APPLICATION

	Application app;

	try
	{
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
#else

	RenderWindow window(VideoMode(1920, 1080), "Wingman Game", Style::Default);

	Clock clock;
	float dt = 0.f;

	Game game(&window);
	GameMapMaker gameMapMaker(&window);

	//Game loop
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();		
		}

		dt = clock.restart().asSeconds();

		if (MAPMAKER)
		{
			gameMapMaker.update(dt);

			window.clear();
			gameMapMaker.draw();
			window.display();
		}
		else
		{
			game.update(dt);

			window.clear();
			game.draw();
			window.display();
		}
	}
#endif


	return 0;
}