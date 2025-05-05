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
	static bool IsOpened() { return opened; } /////////////
	static void ChangeOpened() { opened = !opened; } //////////////
	void ChangeToSelected(RenderWindow& window);
	int LevelPressed()
	{
		return levelSelected;
	}
private:
	inline static bool opened = false; //????????????????
	int levelSelected;
	Font font;
	vector<Text> levels;
};

