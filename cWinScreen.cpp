#include "cWinScreen.h"
#include "cMainMenu.h"
#include "cGame.h"

cWinScreen::cWinScreen(int widthScreen, int heightScreen)
{
	font = sf::Font("../assets/fonts/jersey25.ttf");
	const float widthText = 300.0f;
	float xPos = (float)widthScreen / 2 - widthText / 2;
	float yPos = (float)heightScreen / 2 - 200;
	float yOffset = 100.0f;
	//Text
	auto textContinue = sf::Text(font, "You won!", 100);
	textContinue.setFillColor(Color::Green);
	textContinue.setPosition({ xPos, yPos});
	items.push_back(textContinue);
	//next level
	auto textLoadLevel = sf::Text(font, "Next Level", 70);
	textLoadLevel.setFillColor(Color::Black);
	textLoadLevel.setPosition({ xPos, yPos + yOffset });
	items.push_back(textLoadLevel);
	//back
	auto textOptions = sf::Text(font, "Back to main menu", 70);
	textOptions.setFillColor(Color::Black);
	textOptions.setPosition({ xPos, yPos + 2*yOffset });
	items.push_back(textOptions);
	
	winMenuSelected = 0;
}
cWinScreen::~cWinScreen()
{

}
//Draw win menu
void cWinScreen::Draw(RenderWindow& window)
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
void cWinScreen::MoveUp()
{
	if (winMenuSelected >= 0)
	{
		items[winMenuSelected].setFillColor(Color::Black);
		winMenuSelected--;
		if (winMenuSelected == -1)
		{
			winMenuSelected = items.size() - 1;
		}
		items[winMenuSelected].setFillColor(Color::Green);
	}
}
//move down
void cWinScreen::MoveDown()
{
	if (winMenuSelected <= items.size() - 1)
	{
		items[winMenuSelected].setFillColor(Color::Black);
		winMenuSelected++;
		if (winMenuSelected == items.size())
		{
			winMenuSelected = 0;
		}
		items[winMenuSelected].setFillColor(Color::Green);
	}
}
void cWinScreen::ChangeToSelected(RenderWindow& window)
{
	cGame* game = cGame::Get();
	switch (winMenuSelected)
	{
	case 0: break; //text
	case 1: cWinScreen::ChangeOpened(); break; //next level
	case 2: cWinScreen::ChangeOpened(); cMainMenu::ChangeOpened(); break; //back
	}
}
//event handling
void cWinScreen::EventHandle(optional<Event> event, RenderWindow& window)
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