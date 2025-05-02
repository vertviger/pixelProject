#include "cGame.h"
#include "cScene.h"
#include "cEntity.h"
#include <memory>
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
void cGame::start()
{
	cScene::Get()->AddEnity();
}

