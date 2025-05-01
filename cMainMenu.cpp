#include "cMainMenu.h"


cMainMenu::cMainMenu(int width, int height)
{
	font = sf::Font("../fonts/jersey25.ttf");
	//play
	auto textContinue = sf::Text(font, "Continue", 70);
	textContinue.setFillColor(Color::Green);
	textContinue.setPosition({ 400, 200 });
	items.push_back(textContinue);
	//new game
	auto textLoadLevel = sf::Text(font, "Choose level", 70);
	textLoadLevel.setFillColor(Color::Black);
	textLoadLevel.setPosition({ 400, 300 });
	items.push_back(textLoadLevel);
	//options
	auto textOptions = sf::Text(font, "Options", 70);
	textOptions.setFillColor(Color::Black);
	textOptions.setPosition({ 400, 400 });
	items.push_back(textOptions);
	//exit
	auto textExit = sf::Text(font, "Exit", 70);
	textExit.setFillColor(Color::Black);
	textExit.setPosition({ 400, 500 });
	items.push_back(textExit);

	MainMenuSelected = 0;
}
cMainMenu::~cMainMenu()
{

}
//Draw main menu
void cMainMenu::draw(RenderWindow& window)
{
	for (int i = 0; i < items.size(); i++)
	{
		window.draw(items[i]);
	}
}
//move up
void cMainMenu::MoveUp()
{
	if (MainMenuSelected >= 0)
	{
		items[MainMenuSelected].setFillColor(Color::Black);
		MainMenuSelected--;
		if (MainMenuSelected == -1)
		{
			MainMenuSelected = items.size()-1;
		}
		items[MainMenuSelected].setFillColor(Color::Green);
	}
}
void cMainMenu::MoveDown()
{
	if (MainMenuSelected <= items.size()-1)
	{
		items[MainMenuSelected].setFillColor(Color::Black);
		MainMenuSelected++;
		if (MainMenuSelected == items.size())
		{
			MainMenuSelected = 0;
		}
		items[MainMenuSelected].setFillColor(Color::Green);
	}
}
