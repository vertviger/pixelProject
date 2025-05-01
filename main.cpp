#include <SFML/Graphics.hpp>
#include "cMainMenu.h"
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
    window.setIcon(icon.getSize(), icon.getPixelsPtr());
    cMainMenu mainMenu(window.getSize().x, window.getSize().y);
    while (window.isOpen())
    {
        while (auto const event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (auto const keyEvent = event->getIf<sf::Event::KeyReleased>())
            {
                switch (keyEvent->code)
                {
                case sf::Keyboard::Key::Up: mainMenu.MoveUp();      break;
                case sf::Keyboard::Key::Down: mainMenu.MoveDown();  break;
                //case sf::Keyboard::Key::Enter: window.close();      break;
                }
            }
        }
        window.clear(sf::Color::White);
        mainMenu.draw(window);
        window.display();
    }
}