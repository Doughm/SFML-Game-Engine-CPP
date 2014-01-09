//SFML C++ 2D Game Engine 1.0
//Programer Douglas Harvey-Marose
//
// - Known isues -
//   collison detection for entities is bounding box only, can be inaccurate
//   there is a conflict when using sprites and drawing shapes, can mess up shapes
//

#include "program.h"
#include "gametimer.h"
#include <SFML/Graphics.hpp>
#include <vector>
#pragma comment(linker, "/ENTRY:mainCRTStartup")

int main()
{
	Program program;
	program.start();
    return 0;
}

void Program::assetLoader(std::string const& asset)
{
	if(asset == "test")
	{
		window.setBackgroundColor(sf::Color::Black);
		window.addCircle("testShape2", sf::Vector2f(200, 50), sf::Color::Cyan, 50);
		window.addRectangle("testShape3", sf::Vector2f(350,50), 100, 100, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta);
		window.addRectangle("test1" , sf::Vector2f(50,50), 100, 100, sf::Color::Green);
	}
}


void Program::start()
{
	assetLoader("test");
	gameSpeed = 45;
	gameSpeed = 1000000 / gameSpeed;

	while(window.isOpen())
	{
		//game logic
		if (gameTimer.getElapsedTimeMicroseconds() >= gameSpeed)
		{
			//restarts the logic timer clock
			gameTimer.restartClock();
		}

		window.drawAll();
	}
}