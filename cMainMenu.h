#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace sf;

class cMainMenu
{
public: 
	cMainMenu(int width, int height);
	~cMainMenu();
	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	bool isOpened() { return opened; }
	int MainMenuPressed()
	{
		return MainMenuSelected;
	}
private:
	bool opened = false;
	int MainMenuSelected;
	Font font;
	vector<Text> items;
};

