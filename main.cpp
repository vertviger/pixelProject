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
    while (window.isOpen())
    {
        //1.input handling
        while (auto const event = window.pollEvent())
        {
            if (mainMenu.IsOpened())
            {
                mainMenu.EventHandle(event, window);
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
                    case sf::Keyboard::Key::Escape: mainMenu.ChangeOpened(); break;
                }
            }
        }
        //2. Do game control
        
        //3. Do game logic
        
        //4. Draw all
        window.clear(sf::Color::White);
        if (mainMenu.IsOpened()) { mainMenu.Draw(window); }
        else
        {
            cScene::Get()->Draw(window);
        }
        window.display();
    }
}