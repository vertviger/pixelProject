#include <SFML/Graphics.hpp>
#include "cMainMenu.h"
#include "cScene.h"

using namespace sf;

int main()
{
    //make a main window
    auto window = sf::RenderWindow
    (
        sf::VideoMode({ 1920, 1080 }), "CHERWYAK",
        sf::Style::Default, sf::State::Windowed,
        sf::ContextSettings{ .antiAliasingLevel = 8 }
    );
    sf::Image icon;
    if (!icon.loadFromFile("../Visuals/icon.png"))
    {
        return -1;
    }
    auto font = sf::Font("../fonts/jersey25.ttf");
    window.setIcon(icon.getSize(), icon.getPixelsPtr());
    cMainMenu mainMenu(window.getSize().x, window.getSize().y);
    cLevels levels(window.getSize().x, window.getSize().y);
    while (window.isOpen())
    {
        //1.input handling
        while (auto const event = window.pollEvent())
        {
            if (cMainMenu::IsOpened())
            {
                mainMenu.EventHandle(event, window);
            }
            if (cLevels::IsOpened())
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
                case sf::Keyboard::Key::Escape: cMainMenu::ChangeOpened(); break;
                }
            }
        }
        //2. Do game control
        
        //3. Do game logic
        
        //4. Draw all
        window.clear(sf::Color::White);
        if (cMainMenu::IsOpened()) { mainMenu.Draw(window); }
        if (cLevels::IsOpened()) { levels.Draw(window); }
        else { cScene::Get()->Draw(window); }
        window.display();
    }
}