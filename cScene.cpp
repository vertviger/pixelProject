#include "cScene.h"
#include "cEntity.h"
using namespace std;
using namespace sf;

static cScene scene;
cScene::cScene()
{
	/*Texture backgroundTexture;
	backgroundTexture.loadFromFile("../Visuals/MainMenuBackground.png");
	Sprite background(backgroundTexture);*/
}
cScene::~cScene()
{
	for(auto* e : entities)
	{
		delete e;
	}
	entities.clear();
}
cEntity* cScene::AddEnity()
{
	entities.push_back(new cEntity());
	return entities.back();
}
cScene* cScene::Get()
{
	return &scene;
}
void cScene::Draw(sf::RenderWindow& window)
{
	//window.draw(background);
	for (auto* e : entities)
	{
		e->Draw(window);
	}
}
void cScene::EventHandle(optional<Event> event)
{
	cEntity* controlledEnt = ControlledEntity();
	if (auto const keyEvent = event->getIf<Event::KeyPressed>())
	{
		switch (keyEvent->code)
		{
		case Keyboard::Key::W: controlledEnt->Jump(); break;	   //jump
		case Keyboard::Key::S: controlledEnt->Sneak(); break;	  //sneak
		case Keyboard::Key::A: controlledEnt->GoLeft();	break;	 //go right
		case Keyboard::Key::D: controlledEnt->GoRight(); break;	//go left

		}
	}
	if (auto const keyEvent = event->getIf<Event::KeyReleased>())
	{
		switch (keyEvent->code)
		{
		case Keyboard::Key::W: ; break;	   //stop jump
		case Keyboard::Key::S: ; break;	  //stop sneak
		case Keyboard::Key::A: ; break;	 //stop go right
		case Keyboard::Key::D: ; break; //stop go left

		}
	}
}
cEntity* cScene::ControlledEntity()
{
	return entities[0];
}


