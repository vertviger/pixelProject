#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

#pragma once
class cEntity;

class cGame
{
public:
	cGame();
	static cGame& Get();
	void Start();
	void Pause(bool _on) { pause = _on; PauseClock(_on); }
	void PauseClock(bool _pauseState);
	void SetRemainingTime(float _time) { timeToWinSec = timeRemainingSec - _time; clockGame.restart(); }
	void Quant();
	void Draw(sf::RenderWindow& window);
	bool IsRunning() { return running; }
	bool Win() { return win; }
	bool Loose() { return loose; }
	void Save(const std::string& _path) const;
	void Load(const std::string& _path);

private:
	void CheckGameOver();
	bool pause = false;
	bool running = false;
	bool win = false;
	bool loose = false;
	sf::Clock clockGame;
	sf::Clock clockQuant;
	sf::Clock clockEnemySpawn;
	std::vector<cEntity*> trees;
	float timeToWinSec = 60.0;
	float timeRemainingSec = timeToWinSec;
	float timeElapsedSec = 0;
	sf::Text timeLeftVisual;
};