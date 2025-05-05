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
void cScene::Quant(float deltaTimeSec)
{
	for(auto* e : entities)
	{
		e->Quant(deltaTimeSec);
	}
}
void cScene::Draw(sf::RenderWindow& window)
{
	//window.draw(background);
	for (auto* e : entities)
	{
		e->Draw(window);
	}
}

cEntity* cScene::ControlledEntity()
{
	return entities[0];
}