//SFML C++ 2D Game Engine 1.0
//Programer Douglas Harvey-Marose
//
// - Known isues -
//   collison detection for entities is bounding box only, can be inaccurate
//   if the 0,0 spot on a given sprite sheet is any color but white, the rectangle or quad shapes won't show right
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
		window.setFont("arial.ttf");
		window.addSpriteSheet("smiley.png");
		window.addSpriteMap("smiley", sf::Vector2f(0,1), 95, 98);
		window.setBackgroundColor(sf::Color::Black);
		window.addCircle("circle1", sf::Vector2f(200, 50), sf::Color::Cyan, 50);
		window.addRectangle("rectangle1" , sf::Vector2f(50,50), 100, 100, sf::Color::Green);
		window.addRectangle("rectangle2", sf::Vector2f(350,50), 100, 100, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta);
		window.addText("text1", sf::Vector2f(200,200), sf::Color::Red, 30, "test test test");
		window.addSprite("sprite1", "smiley", sf::Vector2f(50,200));
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