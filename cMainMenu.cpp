#include "cMainMenu.h"
#include "cGame.h"
#include "cMenuSaves.h"
#include "cGraphics.h"

cMainMenu::cMainMenu(int width, int height) : background(GetTexture(AssetsPath() + "Visuals/mainMenuFrame.png"))
{
	auto& font = GetFont();
	//play
	auto textContinue = sf::Text(font, "Continue", 70);
	textContinue.setFillColor(Color::Green);
	textContinue.setPosition({ 400, 200 });
	items.push_back(textContinue);
	//new game
	auto textLoadLevel = sf::Text(font, "Choose save", 70);
	textLoadLevel.setFillColor(Color::White);
	textLoadLevel.setPosition({ 400, 300 });
	items.push_back(textLoadLevel);
	//options
	auto textOptions = sf::Text(font, "Options", 70);
	textOptions.setFillColor(Color::White);
	textOptions.setPosition({ 400, 400 });
	items.push_back(textOptions);
	//exit
	auto textExit = sf::Text(font, "Exit", 70);
	textExit.setFillColor(Color::White);
	textExit.setPosition({ 400, 500 });
	items.push_back(textExit);
	
	background.setPosition({ 325, 135 });
	mainMenuSelected = 0;
}
//Draw main menu
void cMainMenu::Draw(RenderWindow& window)
{
	window.draw(background);
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
		items[mainMenuSelected].setFillColor(Color::White);
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
		items[mainMenuSelected].setFillColor(Color::White);
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
	case 0: if (!game->IsRunning() || game->Win() || game->Loose()) { game->Start(); cMainMenu::ChangeOpened(); }
		  else { game->Pause(false); cMainMenu::ChangeOpened(); }  break; //continue
	case 1: cMenuSaves::ChangeOpened(); cMainMenu::ChangeOpened(); break; //levels list
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

