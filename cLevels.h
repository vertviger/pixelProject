#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "cMainMenu.h"
#include "cGame.h"



using namespace std;
using namespace sf;

class cLevels
{
public:
	cLevels(int width, int height);
	~cLevels();
	void Draw(RenderWindow& window);
	void EventHandle(optional<Event> event, RenderWindow& window);
	void MoveUp();
	void MoveDown();
	bool IsOpened() { return opened; }
	bool ChangeOpened() { return opened = !opened; }
	void ChangeToSelected(RenderWindow& window);
	int LevelPressed()
	{
		return levelSelected;
	}
private:
	bool opened = false;
	int levelSelected;
	Font font;
	vector<Text> levels;
};

