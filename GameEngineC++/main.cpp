//SFML C++ 2D Game Engine 1.0
//Programer Douglas Harvey-Marose
//
//
// - Version Changes 1.1
//   changed the audio on-off to set rather than toggle
//   changed the string bindings for A-Z keys to make sorting strings easier
//	 added the network class to the VS project
//	 added the textedit class
//
//
// - Known isues -
//   collison detection for entities is bounding box only, can be inaccurate
//   if the 0,0 spot on a given sprite sheet is any color but white, the rectangle or quad shapes won't show right
//

#include "gametimer.h"
#include "window.h"
#include "assetloader.h"
#include <SFML/Graphics.hpp>
#include <vector>
#pragma comment(linker, "/ENTRY:mainCRTStartup")

int main()
{
	Window* window = new Window();
	AssetLoader assetLoader(window);
	GameTimer gameTimer;

	assetLoader.loadBaseAssets();
	float gameSpeed;
	gameSpeed = 45;
	gameSpeed = 1000000 / gameSpeed;

	while (window->isOpen())
	{
		//game logic
		if (gameTimer.getElapsedTimeMicroseconds() >= gameSpeed)
		{
			//restarts the logic timer clock
			gameTimer.restartClock();
		}

		window->drawAll();
	}

	delete window;
    return 0;
}