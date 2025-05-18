#include "cOptionsMenu.h"
#include "cMainMenu.h"
#include "cGame.h"
#include "cGraphics.h"

cOptionsMenu::cOptionsMenu(int width, int height)
{
	auto& font = GetFont();
	//text
	auto textText = sf::Text(font, "Choose difficulty", 80);
	textText.setFillColor(Color::Green);
	textText.setPosition({ 400, 180 });
	items.push_back(textText);
	//Easy
	auto textEasy = sf::Text(font, "Easy", 70);
	textEasy.setFillColor(Color::White);
	textEasy.setPosition({ 400, 300 });
	items.push_back(textEasy);
	//Medium
	auto textMedium = sf::Text(font, "Medium", 70);
	textMedium.setFillColor(Color::White);
	textMedium.setPosition({ 400, 400 });
	items.push_back(textMedium);
	//Hard
	auto textHard = sf::Text(font, "Hard", 70);
	textHard.setFillColor(Color::White);
	textHard.setPosition({ 400, 500 });
	items.push_back(textHard);
	//insane
	auto textInsane = sf::Text(font, "Insane", 70);
	textInsane.setFillColor(Color::White);
	textInsane.setPosition({ 400, 600 });
	items.push_back(textInsane);
	//exit
	auto textExit = sf::Text(font, "Go Back", 70);
	textExit.setFillColor(Color::White);
	textExit.setPosition({ 400, 700 });
	items.push_back(textExit);
	difficultySelected = 0;
}
//Draw main menu
void cOptionsMenu::Draw(RenderWindow& window)
{
	for (int i = 0; i < items.size(); i++)
	{
		window.draw(items[i]);
	}
	opened = true;
}
//move up
//move up
void cOptionsMenu::MoveUp()
{
	if (difficultySelected >= 0)
	{
		items[difficultySelected].setFillColor(Color::White);
		difficultySelected--;
		if (difficultySelected == -1)
		{
			difficultySelected = items.size() - 1;
		}
		if (difficultySelected != 0) items[difficultySelected].setFillColor(Color::Green);
	}
}
//move down
void cOptionsMenu::MoveDown()
{
	if (difficultySelected <= items.size() - 1)
	{
		items[difficultySelected].setFillColor(Color::White);
		difficultySelected++;
		if (difficultySelected == items.size())
		{
			difficultySelected = 0;
		}
		if (difficultySelected != 0) items[difficultySelected].setFillColor(Color::Green);
		//levels[difficultySelected].setFillColor(Color::Green);
	}
}
void cOptionsMenu::ChangeToSelected(RenderWindow& window)
{
	switch (difficultySelected)
	{
	case 0: break; 	   //text
	case 1: cGame::Get().Difficulty(cGame::Get().EASY); difficultySelected = 0; ChangeOpened(); cMainMenu::ChangeOpened();   break;	   //Easy
	case 2: cGame::Get().Difficulty(cGame::Get().NORMAL); difficultySelected = 0; ChangeOpened(); cMainMenu::ChangeOpened(); break;	  //Medium
	case 3:	cGame::Get().Difficulty(cGame::Get().HARD); difficultySelected = 0; ChangeOpened(); cMainMenu::ChangeOpened();   break;  //Hard
	case 4:	cGame::Get().Difficulty(cGame::Get().INSANE); difficultySelected = 0; ChangeOpened(); cMainMenu::ChangeOpened(); break; //Insane
	case 5:	difficultySelected = 0; ChangeOpened(); cMainMenu::ChangeOpened();											     break;//GoBack
	}
}
//event handling
void cOptionsMenu::EventHandle(optional<Event> event, RenderWindow& window)
{
	if (auto const keyEvent = event->getIf<sf::Event::KeyReleased>())
	{
		switch (keyEvent->code)
		{
		case sf::Keyboard::Key::Up: MoveUp();								                  break;
		case sf::Keyboard::Key::Down: MoveDown();											  break;
		case sf::Keyboard::Key::Enter: ChangeToSelected(window);							  break;
		case sf::Keyboard::Key::Escape: ChangeOpened();										  break;
		}
	}
}

