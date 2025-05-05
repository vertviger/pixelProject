#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

#pragma once

class cGame
{
public:
	static cGame* Get();
	void Start();
	void Pause(bool _on) { pause = _on; }
	void Quant();
	void Draw(sf::RenderWindow& window);
private:
	bool pause = false;
	bool running = false;
	sf::Clock clock;
	sf::Time passedFromLastQuant = sf::Time::Zero;
};