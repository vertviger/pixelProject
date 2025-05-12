#include <SFML/Graphics.hpp>
#include "cMainMenu.h"
#include "cScene.h"
#include "cGameControl.h"
#include "cMenuLevels.h"
#include "cGame.h"

using namespace sf;

const std::string& AssetsPath()
{
	static const std::string assetsPath = "../assets/";
	return assetsPath;
}

int main()
{
    //make a main window
    auto window = sf::RenderWindow
    (
        sf::VideoMode({ 1920, 1080 }), "DefendTheForest",
        sf::Style::Default, sf::State::Windowed,
        sf::ContextSettings{ .antiAliasingLevel = 8 }
    );
    sf::Image icon;
    if (!icon.loadFromFile(AssetsPath() + "Visuals/icon2.png"))
    {
        return -1;
    }
    auto font = sf::Font(AssetsPath() + "fonts/jersey25.ttf");
    window.setIcon(icon.getSize(), icon.getPixelsPtr());
    cMainMenu mainMenu(window.getSize().x, window.getSize().y);
    cMenuLevels levels(window.getSize().x, window.getSize().y);
    while (window.isOpen())
    {
        //1.input handling
        while (auto const event = window.pollEvent())
        {
            if (cMainMenu::IsOpened())
            {
                mainMenu.EventHandle(event, window);
            }
            if (cMenuLevels::IsOpened())
            {
                levels.EventHandle(event, window);
            }
            else
            {

            }
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (auto const keyEvent = event->getIf<sf::Event::KeyReleased>())
            {
                switch (keyEvent->code)
                {
                case sf::Keyboard::Key::Escape: cMainMenu::ChangeOpened(); cGame::Get()->Pause(mainMenu.IsOpened()); break;
                }
            }
            //2. Do game control
            cGameControl::Get()->EventHandle(event);
        }
        
        //3. Do game logic
        cGame::Get()->Quant();

        //4. Draw all
        window.clear(sf::Color::White);
        if (cMainMenu::IsOpened()) { mainMenu.Draw(window);}
        if (cMenuLevels::IsOpened()) { levels.Draw(window); }
        if (cGame::Get()->Win()) { /*winScreen.Draw(window);*/ }
        if (cGame::Get()->Loose()) { /*looseScreen.Draw(window);*/ }
        else 
        { 
            
            cScene::Get()->Draw(window); 
            cGame::Get()->Draw(window);
        }
        window.display();
    }
}