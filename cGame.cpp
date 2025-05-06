#include "cGame.h"
#include "cScene.h"
#include "cEntity.h"
#include <memory>
#include "cGameControl.h"
using namespace std;

cGame* cGame::Get()
{
	static cGame game;
	return &game;
}
void cGame::Start()
{
	auto hero = cScene::Get()->AddEnity("hero");
	cGameControl::Get()->ControledEntity(hero);
	clock.restart();
	running = true;
}
void cGame::Quant()
{
	Time delta = clock.restart();
	if(pause) return;
	passedFromLastQuant += delta;
	const float quantPeriodMs = 10.0f;
	if(passedFromLastQuant.asMicroseconds() > quantPeriodMs)
	{
		cScene::Get()->Quant(passedFromLastQuant.asSeconds());
		passedFromLastQuant = sf::Time::Zero;
	}
}
void cGame::Draw(sf::RenderWindow& window)
{
	if (!running) return;
	cGameControl::Get()->Draw(window);
}
