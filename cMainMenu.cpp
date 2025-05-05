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

	mainMenuSelected = 0;
}
cMainMenu::~cMainMenu()
{

}
//Draw main menu
void cMainMenu::Draw(RenderWindow& window)
{
	for (int i = 0; i < items.size(); i++)
	{
		window.draw(items[i]);
	}
	opened = true;
}
//move up
void cMainMenu::MoveUp()
{
	if (mainMenuSelected >= 0)
	{
		items[mainMenuSelected].setFillColor(Color::Black);
		mainMenuSelected--;
		if (mainMenuSelected == -1)
		{
			mainMenuSelected = items.size()-1;
		}
		items[mainMenuSelected].setFillColor(Color::Green);
	}
}
//move down
void cMainMenu::MoveDown()
{
	if (mainMenuSelected <= items.size()-1)
	{
		items[mainMenuSelected].setFillColor(Color::Black);
		mainMenuSelected++;
		if (mainMenuSelected == items.size())
		{
			mainMenuSelected = 0;
		}
		items[mainMenuSelected].setFillColor(Color::Green);
	}
}
void cMainMenu::ChangeToSelected(RenderWindow& window)
{
	cGame* game = cGame::Get();
	switch (mainMenuSelected)
	{
	case 0: game->Start(); cMainMenu::ChangeOpened(); break; //continue
	case 1: cLevels::ChangeOpened(); cMainMenu::ChangeOpened(); break; //levels list
	case 2: break;				//options
	case 3:	window.close(); break; //exit
	}
}
//event handling
void cMainMenu::EventHandle(optional<Event> event, RenderWindow& window)
{
	if (auto const keyEvent = event->getIf<sf::Event::KeyReleased>())
	{
		switch (keyEvent->code)
		{
		case sf::Keyboard::Key::Up: MoveUp();								  break;
		case sf::Keyboard::Key::Down: MoveDown();							  break;
		case sf::Keyboard::Key::Enter: ChangeToSelected(window);      break;
		}
	}
}

