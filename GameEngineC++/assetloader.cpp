#include "assetloader.h"

AssetLoader::AssetLoader(Window * passedWindow)
{
	window = passedWindow;
}

AssetLoader::~AssetLoader()
{
	window = NULL;
}

//loads in the staring assests
void AssetLoader::loadBaseAssets()
{
	window->setFont("arial.ttf");
	window->addSpriteSheet("smiley.png");
	window->addSpriteMap("smiley", sf::Vector2f(0, 1), 95, 98);
	window->setBackgroundColor(sf::Color::Black);
	window->addCircle("circle1", sf::Vector2f(200, 50), sf::Color::Cyan, 50);
	window->addRectangle("rectangle1", sf::Vector2f(50, 50), 100, 100, sf::Color::Green);
	window->addRectangle("rectangle2", sf::Vector2f(350, 50), 100, 100, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta);
	window->addText("text1", sf::Vector2f(200, 200), sf::Color::Red, 30, "test test test");
	window->addSprite("sprite1", "smiley", sf::Vector2f(50, 200));
}