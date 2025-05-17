#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

class cLooseScreen
{
public:
	cLooseScreen(int width, int height);
	~cLooseScreen();
	void Draw(RenderWindow& window);
	void EventHandle(optional<Event> event, RenderWindow& window);
	void MoveUp();
	void MoveDown();
	static bool IsOpened() { return opened; }
	static void ResetCounter() { counter = 0; }
	static void ChangeOpened() { opened = !opened; }
	static void GameLost() { if (counter == 0) opened = !opened; counter++; }
	void ChangeToSelected(RenderWindow& window);
	int LooseScreenPressed() { return looseMenuSelected; }
private:
	inline static int counter = 0;
	inline static bool opened = false;
	int looseMenuSelected;
	vector<Text> items;
};


