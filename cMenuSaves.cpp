#include "cMenuSaves.h"
#include "cGraphics.h"

cMenuSaves::cMenuSaves(int width, int height)
{
	auto& font = GetFont();
	//1
	auto textF = sf::Text(font, "Save/Load Game", 60);
	textF.setFillColor(Color::White);
	textF.setPosition({ 400, 100 });
	levels.push_back(textF);
	//1
	auto text1 = sf::Text(font, "Save to File1", 60);
	text1.setFillColor(Color::Green);
	text1.setPosition({ 400, 200 });
	levels.push_back(text1);
	//2
	auto text2 = sf::Text(font, "Save to File2", 60);
	text2.setFillColor(Color::White);
	text2.setPosition({ 400, 300 });
	levels.push_back(text2);
	//3
	auto text3 = sf::Text(font, "Save to File3", 60);
	text3.setFillColor(Color::White);
	text3.setPosition({ 400, 400 });
	levels.push_back(text3);
	//4
	auto text4 = sf::Text(font, "Load from File1", 60);
	text4.setFillColor(Color::White);
	text4.setPosition({ 400, 500 });
	levels.push_back(text4);
	//5
	auto text5 = sf::Text(font, "Load from File2", 60);
	text5.setFillColor(Color::White);
	text5.setPosition({ 400, 600 });
	levels.push_back(text5);
	//6
	auto text6 = sf::Text(font, "Load from File3", 60);
	text6.setFillColor(Color::White);
	text6.setPosition({ 400, 700 });
	levels.push_back(text6);
	//back
	auto textBack = sf::Text(font, "Go back", 60);
	textBack.setFillColor(Color::White);
	textBack.setPosition({ 400, 800 });
	levels.push_back(textBack);

	levelSelected = 0;
}
cMenuSaves::~cMenuSaves()
{

}
//drawing
void cMenuSaves::Draw(RenderWindow& window)
{
	for (int i = 0; i < levels.size(); i++)
	{
		window.draw(levels[i]);
	}
	opened = true;
}
//move up
void cMenuSaves::MoveUp()
{
	if (levelSelected >= 0)
	{
		levels[levelSelected].setFillColor(Color::White);
		levelSelected--;
		if (levelSelected == -1)
		{
			levelSelected = levels.size() - 1;
		}
		if(levelSelected != 0) levels[levelSelected].setFillColor(Color::Green);
	}
}
//move down
void cMenuSaves::MoveDown()
{
	if (levelSelected <= levels.size() - 1)
	{
		levels[levelSelected].setFillColor(Color::White);
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
void cMenuSaves::ChangeToSelected(RenderWindow& window)
{
	cGame& game = cGame::Get();
	switch (levelSelected)
	{
	case 0:	break; //Manual(possibly)
	case 1: game.Save("Save1"); levels[levelSelected].setFillColor(Color::White); levelSelected = 0;break; //Save1
	case 2: game.Save("Save2"); levels[levelSelected].setFillColor(Color::White); levelSelected = 0;break; //Save2
	case 3:	game.Save("Save3"); levels[levelSelected].setFillColor(Color::White); levelSelected = 0;break; //Save3
	case 4:	game.Load("Save1"); levels[levelSelected].setFillColor(Color::White); levelSelected = 0;break; //Load1
	case 5:	game.Load("Save2"); levels[levelSelected].setFillColor(Color::White); levelSelected = 0;break; //Load2
	case 6:	game.Load("Save3"); levels[levelSelected].setFillColor(Color::White); levelSelected = 0;break; //Load3
	case 7:	cMainMenu::ChangeOpened(); cMenuSaves::ChangeOpened(); levelSelected = 0;break; //back
	}
}
//event handling
void cMenuSaves::EventHandle(optional<Event> event, RenderWindow& window)
{
	if (auto const keyEvent = event->getIf<sf::Event::KeyReleased>())
	{
		switch (keyEvent->code)
		{
		case sf::Keyboard::Key::Up: MoveUp();						  break;
		case sf::Keyboard::Key::Down: MoveDown();					  break;
		case sf::Keyboard::Key::Enter: ChangeToSelected(window);      break;
		case sf::Keyboard::Key::Escape: cMenuSaves::ChangeOpened();      break;
		}
	}
}
