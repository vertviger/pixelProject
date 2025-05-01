#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace sf;

class cMainMenu
{
public: 
	cMainMenu(float width, float height);
	~cMainMenu();
	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();

	int MainMenuPressed()
	{
		return MainMenuSelected;
	}
private:
	int MainMenuSelected;
	Font font;
	vector<Text> items;
};

