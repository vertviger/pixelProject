#include "cLooseScreen.h"
#include "cGraphics.h"
#include "cMainMenu.h"
#include "cMenuSaves.h"
#include "cGame.h"

cLooseScreen::cLooseScreen(int widthScreen, int heightScreen)
{
	auto& font = GetFont();
	const float widthText = 300.0f;
	float xPos = (float)widthScreen / 2 - widthText / 2;
	float yPos = (float)heightScreen / 2 - 200;
	float yOffset = 100.0f;
	//Text
	auto textContinue = sf::Text(font, "You Lost!", 100);
	textContinue.setFillColor(Color::Red);
	textContinue.setPosition({ 400, 200 });
	//textContinue.setPosition({ xPos, yPos });
	items.push_back(textContinue);
	//next level
	auto textLoadLevel = sf::Text(font, "Retry", 70);
	textLoadLevel.setFillColor(Color::White);
	textLoadLevel.setPosition({ 400, 350 });
	//textLoadLevel.setPosition({ xPos, yPos + yOffset });
	items.push_back(textLoadLevel);
	//choose save
	auto textChooseSave = sf::Text(font, "Choose Save", 70);
	textChooseSave.setFillColor(Color::White);
	textChooseSave.setPosition({ 400, 450 });
	//textLoadLevel.setPosition({ xPos, yPos + yOffset });
	items.push_back(textChooseSave);
	//back
	auto textOptions = sf::Text(font, "Back to main menu", 70);
	textOptions.setFillColor(Color::White);
	textOptions.setPosition({ 400, 550 });
	//textOptions.setPosition({ xPos, yPos + 2*yOffset });
	items.push_back(textOptions);
	
	looseMenuSelected = 0;
}
cLooseScreen::~cLooseScreen()
{

}
//Draw main menu
void cLooseScreen::Draw(RenderWindow& window)
{
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
		items[looseMenuSelected].setFillColor(Color::White);
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
		items[looseMenuSelected].setFillColor(Color::White);
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
	cGame& game = cGame::Get();
	switch (looseMenuSelected)
	{
	case 0: break; //text
	case 1: cLooseScreen::ChangeOpened(); game.Start(); break; //next level
	case 2: cLooseScreen::ChangeOpened(); cMenuSaves::ChangeOpened(); break; //back
	case 3: cLooseScreen::ChangeOpened(); cMainMenu::ChangeOpened(); break; //back
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