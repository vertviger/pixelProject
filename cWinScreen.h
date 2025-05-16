#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

class cWinScreen
{
public:
	cWinScreen(int width, int height);
	~cWinScreen();
	void Draw(RenderWindow& window);
	void EventHandle(optional<Event> event, RenderWindow& window);
	void MoveUp();
	void MoveDown();
	static bool IsOpened() { return opened; }
	static void ResetCounter() { counter = 0; }
	static void ChangeOpened() { opened = !opened; }
	static void GameWon() { if (counter == 0) opened = !opened; counter++; }
	void ChangeToSelected(RenderWindow& window);
	int WinScreenPressed() { return winMenuSelected; }
private:
	inline static int counter = 0;
	inline static bool opened = false;
	int winMenuSelected;
	Font font;
	vector<Text> items;
};


