#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


using namespace std;
using namespace sf;

class cOptionsMenu
{
public: 
	cOptionsMenu(int width, int height);
	void Draw(RenderWindow& window);
	void EventHandle(optional<Event> event, RenderWindow& window);
	void MoveUp();
	void MoveDown();
	static bool IsOpened() { return opened; }
	static void ChangeOpened() { opened = !opened; }
	void ChangeToSelected(RenderWindow& window);
	int difficultyPressed()
	{
		return difficultySelected;
	}
private:
	inline static bool opened = false;
	int difficultySelected;
	vector<Text> items;
};

