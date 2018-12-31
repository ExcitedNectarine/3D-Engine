#include "Application.h"
#include "MainMenuScene.h"

int main(int argc, char* argv[])
{
	try
	{
		ENG::Application app;
		app.getSceneManager().addScene<MainMenuScene>();
		app.run();
	}
	catch (const ENG::ApplicationException& error)
	{
		OUTPUT_ERROR(error.what());
		std::cin.get();
	}

	return 0;
}