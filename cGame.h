#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#pragma once

class cGame
{
public:
	static cGame* Get();
	void Start();
	void Pause(bool _on) { pause = _on; }
	void Quant();

private:
	bool pause = false;
	sf::Clock clock;
	sf::Time passedFromLastQuant = sf::Time::Zero;
};