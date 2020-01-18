#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#else
#error "Unrecognized configuration!"
#endif


#include <SFML\Graphics.hpp>

#include "LevelController.h"

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{


	try {
		LevelController::getInstace().run();
	}
	catch (std::exception &e)
	{
		ResourceManeger::getInstance().sendErrorBox("Error",e.what());
	}

	return 0;
}