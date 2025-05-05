#include "cGame.h"
#include "cScene.h"
#include "cEntity.h"
#include <memory>
#include "cGameControl.h"
using namespace std;

static std::unique_ptr<cGame> game;

cGame* cGame::Get()
{
	if (!game)
	{
		game = std::make_unique<cGame>();
	}
	return game.get();
}
void cGame::Start()
{
	cScene::Get()->AddEnity();
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
