#include "cMenuLevels.h"

cMenuLevels::cMenuLevels(int width, int height)
{
	font = sf::Font("../assets/fonts/jersey25.ttf");
	//1
	auto textStart = sf::Text(font, "Choose a level", 60);
	textStart.setFillColor(Color::Black);
	textStart.setPosition({ 400, 100 });
	levels.push_back(textStart);
	//1
	auto textlvl1 = sf::Text(font, "Level 1", 60);
	textlvl1.setFillColor(Color::Green);
	textlvl1.setPosition({ 400, 200 });
	levels.push_back(textlvl1);
	//2
	auto textlvl2 = sf::Text(font, "Level 2", 60);
	textlvl2.setFillColor(Color::Black);
	textlvl2.setPosition({ 400, 300 });
	levels.push_back(textlvl2);
	//3
	auto textlvl3 = sf::Text(font, "Level 3", 60);
	textlvl3.setFillColor(Color::Black);
	textlvl3.setPosition({ 400, 400 });
	levels.push_back(textlvl3);
	//4
	auto textlvl4 = sf::Text(font, "Level 4", 60);
	textlvl4.setFillColor(Color::Black);
	textlvl4.setPosition({ 400, 500 });
	levels.push_back(textlvl4);
	//5
	auto textlvl5 = sf::Text(font, "Level 5", 60);
	textlvl5.setFillColor(Color::Black);
	textlvl5.setPosition({ 400, 600 });
	levels.push_back(textlvl5);
	//back
	auto textBack = sf::Text(font, "Go back", 60);
	textBack.setFillColor(Color::Black);
	textBack.setPosition({ 400, 700 });
	levels.push_back(textBack);

	levelSelected = 0;
}
cMenuLevels::~cMenuLevels()
{

}
//drawing
void cMenuLevels::Draw(RenderWindow& window)
{
	for (int i = 0; i < levels.size(); i++)
	{
		window.draw(levels[i]);
	}
	opened = true;
}
//move up
void cMenuLevels::MoveUp()
{
	if (levelSelected >= 0)
	{
		levels[levelSelected].setFillColor(Color::Black);
		levelSelected--;
		if (levelSelected == -1)
		{
			levelSelected = levels.size() - 1;
		}
		if(levelSelected != 0) levels[levelSelected].setFillColor(Color::Green);
	}
}
//move down
void cMenuLevels::MoveDown()
{
	if (levelSelected <= levels.size() - 1)
	{
		levels[levelSelected].setFillColor(Color::Black);
		levelSelected++;
		if (levelSelected == levels.size())
		{
			levelSelected = 0;
		}
		if (levelSelected != 0) levels[levelSelected].setFillColor(Color::Green);
		//levels[levelSelected].setFillColor(Color::Green);
	}
}
//selecting
void cMenuLevels::ChangeToSelected(RenderWindow& window)
{
	cGame* game = cGame::Get();
	switch (levelSelected)
	{
	case 0:	break; //Manual(possibly)
	case 1: if (!game->IsRunning()) { game->Start(); cMenuLevels::ChangeOpened(); levelSelected = 0; }
		  else { game->Pause(false); cMenuLevels::ChangeOpened(); levelSelected = 0; }  break; //level1
	case 2: break; //level2
	case 3:	break; //level3
	case 4:	break; //level4
	case 5:	break; //level5
	case 6:	cMainMenu::ChangeOpened(); cMenuLevels::ChangeOpened(); levelSelected = 0;break; //back

	}
}
//event handling
void cMenuLevels::EventHandle(optional<Event> event, RenderWindow& window)
{
	if (auto const keyEvent = event->getIf<sf::Event::KeyReleased>())
	{
		switch (keyEvent->code)
		{
		case sf::Keyboard::Key::Up: MoveUp();						  break;
		case sf::Keyboard::Key::Down: MoveDown();					  break;
		case sf::Keyboard::Key::Enter: ChangeToSelected(window);      break;
		case sf::Keyboard::Key::Escape: cMenuLevels::ChangeOpened();      break;
		}
	}
}
