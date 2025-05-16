#include <SFML/Graphics.hpp>
#include "cMainMenu.h"
#include "cScene.h"
#include "cGameControl.h"
#include "cMenuLevels.h"
#include "cWinScreen.h"
#include "cLooseScreen.h"
#include "cGame.h"

using namespace sf;


const std::string& AssetsPath()
{
	static const std::string assetsPath = "../assets/";
	return assetsPath;
}
sf::Vector2u windowSize = { 1920, 1080 };
sf::Vector2u windowSizeCurrent = windowSize;

sf::Vector2f MouseToScene(sf::Vector2i mousePosition)
{
    auto scene = cScene::Get();
    float kx = windowSizeCurrent.x / scene->GetSize().x;
    float ky = windowSizeCurrent.y / scene->GetSize().y;
    Vector2f pos = { mousePosition.x / kx, mousePosition.y / ky };
    return pos;
}

int main()
{
    //make a main window
    std::srand(std::time({}));
    auto window = sf::RenderWindow
    (
        sf::VideoMode(windowSize), "DefendTheForest",
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
    cWinScreen winScreen(window.getSize().x, window.getSize().y);
    cLooseScreen looseScreen(window.getSize().x, window.getSize().y);
    while (window.isOpen())
    {
        //1.input handling
        while (auto const event = window.pollEvent())
        {
            if (cMainMenu::IsOpened()) mainMenu.EventHandle(event, window);
            
            if (cMenuLevels::IsOpened()) levels.EventHandle(event, window);
            
            if (cWinScreen::IsOpened()) winScreen.EventHandle(event, window);

            if (cLooseScreen::IsOpened()) looseScreen.EventHandle(event, window);

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                windowSizeCurrent = resized->size;
            }
            else if (auto const keyEvent = event->getIf<sf::Event::KeyReleased>())
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
        if (cGame::Get()->Win())
        {
            cWinScreen::GameWon();
        }
        if (cGame::Get()->Loose())
        {
            cLooseScreen::GameLost();
        }

        //4. Draw all
        window.clear(sf::Color::White);
        
        cGame::Get()->Draw(window);
        if (cMainMenu::IsOpened()) { mainMenu.Draw(window);}
        else if (cMenuLevels::IsOpened()) { levels.Draw(window); }
        else if (cWinScreen::IsOpened()) { cGame::Get()->Pause(true); winScreen.Draw(window); }
        else if (cLooseScreen::IsOpened()) { cGame::Get()->Pause(true); looseScreen.Draw(window); }
        else 
        { 
            
        }
        window.display();
    }
}