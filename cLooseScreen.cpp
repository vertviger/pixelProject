#include "cLooseScreen.h"
#include "cMainMenu.h"
#include "cGame.h"

cLooseScreen::cLooseScreen(int widthScreen, int heightScreen)
{
	font = sf::Font("../assets/fonts/jersey25.ttf");
	const float widthText = 300.0f;
	float xPos = (float)widthScreen / 2 - widthText / 2;
	float yPos = (float)heightScreen / 2 - 200;
	float yOffset = 100.0f;
	//Text
	auto textContinue = sf::Text(font, "You Lost!", 100);
	textContinue.setFillColor(Color::Green);
	textContinue.setPosition({ xPos, yPos + yOffset });
	items.push_back(textContinue);
	//next level
	auto textLoadLevel = sf::Text(font, "Retry", 70);
	textLoadLevel.setFillColor(Color::Black);
	textLoadLevel.setPosition({ xPos, yPos });
	items.push_back(textLoadLevel);
	//back
	auto textOptions = sf::Text(font, "Back to main menu", 70);
	textOptions.setFillColor(Color::Black);
	textOptions.setPosition({ xPos, yPos + 2*yOffset });
	items.push_back(textOptions);
	
	looseMenuSelected = 0;
}
cLooseScreen::~cLooseScreen()
{

}
//Draw main menu
void cLooseScreen::Draw(RenderWindow& window)
{
	/*Texture backgroundTexture;
	backgroundTexture.loadFromFile("../assets/Visuals/mainMenuFrame.png");
	Sprite background(backgroundTexture);
	background.setPosition({ 325, 135 });
	window.draw(background);*/
	for (int i = 0; i < items.size(); i++)
	{
		window.draw(items[i]);
	}
	opened = true;
}
//move up
void cLooseScreen::MoveUp()
{
	if (looseMenuSelected >= 0)
	{
		items[looseMenuSelected].setFillColor(Color::Black);
		looseMenuSelected--;
		if (looseMenuSelected == -1)
		{
			looseMenuSelected = items.size() - 1;
		}
		items[looseMenuSelected].setFillColor(Color::Red);
	}
}
//move down
void cLooseScreen::MoveDown()
{
	if (looseMenuSelected <= items.size() - 1)
	{
		items[looseMenuSelected].setFillColor(Color::Black);
		looseMenuSelected++;
		if (looseMenuSelected == items.size())
		{
			looseMenuSelected = 0;
		}
		items[looseMenuSelected].setFillColor(Color::Red);
	}
}
void cLooseScreen::ChangeToSelected(RenderWindow& window)
{
	cGame* game = cGame::Get();
	switch (looseMenuSelected)
	{
	case 0: break; //text
	case 1: cLooseScreen::ChangeOpened(); break; //next level
	case 2: cLooseScreen::ChangeOpened(); cMainMenu::ChangeOpened(); break; //back
	}
}
//event handling
void cLooseScreen::EventHandle(optional<Event> event, RenderWindow& window)
{
	if (auto const keyEvent = event->getIf<sf::Event::KeyReleased>())
	{
		switch (keyEvent->code)
		{
		case sf::Keyboard::Key::Up: MoveUp();								  break;
		case sf::Keyboard::Key::Down: MoveDown();							  break;
		case sf::Keyboard::Key::Enter: ChangeToSelected(window);			  break;
		}
	}
}