#include "cScene.h"
#include "cEntity.h"
using namespace std;
using namespace sf;

cScene::cScene()
{
	/*Texture backgroundTexture;
	backgroundTexture.loadFromFile("../resources/Visuals/level1Background.png");
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
cEntity* cScene::Spawn(const string& _name)
{
	entities.push_back(new cEntity(_name));
	return entities.back();
}
cScene* cScene::Get()
{
	static cScene scene;
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

cEntity* cScene::FindEntity(Vector2f pos)
{
	return nullptr;
}