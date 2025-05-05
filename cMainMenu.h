#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "cMenuLevels.h"
#include "cGame.h"


using namespace std;
using namespace sf;

class cMainMenu
{
public: 
	cMainMenu(int width, int height);
	~cMainMenu();
	void Draw(RenderWindow& window);
	void EventHandle(optional<Event> event, RenderWindow& window);
	void MoveUp();
	void MoveDown();
	static bool IsOpened() { return opened; }
	static bool ChangeOpened() { return opened = !opened; }
	void ChangeToSelected(RenderWindow& window);
	int MainMenuPressed()
	{
		return mainMenuSelected;
	}
private:
	inline static bool opened = true;
	int mainMenuSelected;
	Font font;
	vector<Text> items;
};

