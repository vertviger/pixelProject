#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

#pragma once
class cEntity;

class cGame
{
public:
	static cGame* Get();
	void Start();
	void Pause(bool _on) { pause = _on; }
	void Quant();
	void Draw(sf::RenderWindow& window);
	bool IsRunning() { return running; }
private:
	bool pause = false;
	bool running = false;
	sf::Clock clock;
	sf::Clock clockEnemySpawn;
	sf::Time passedFromLastQuant = sf::Time::Zero;
	std::vector<cEntity*> trees;
};