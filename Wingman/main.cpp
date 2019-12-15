#include <iostream>

#include "Application.h"

int main()
{
	srand(time(NULL));

	Application app;

	try
	{
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}


	return 0;
}