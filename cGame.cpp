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
	auto hero = cScene::Get()->Spawn("player");
	auto scene = cScene::Get();
	sf::Vector2f sceneSize = scene->GetSize();
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			sf::Vector2f pos;
			pos.x = sceneSize.x / 4 + i * sceneSize.x / 2;
			pos.y = sceneSize.y / 4 + j * sceneSize.y / 2;
			auto tree = scene->Spawn("tree");
			tree->ChangePosition(pos);
		}
	}
	cGameControl::Get()->ControledEntity(hero);
	clockGame.restart();
	clockQuant.restart();
	running = true;
}
void cGame::Quant()
{
	if (!running) return;
	cScene* scene = cScene::Get();
	sf::Vector2f sceneSize = scene->GetSize();
	if(pause)
	{
		clockQuant.restart();
		return;
	}
	const float quantPeriodMs = 10.0f;
	float deltaQuant = clockQuant.getElapsedTime().asMilliseconds();
	if(deltaQuant > quantPeriodMs)
	{
		if (clockEnemySpawn.getElapsedTime().asSeconds() >= 5)
		{
			std::vector<string> enemyNames = { "enemyAxe", "enemySaw", "enemyChainSaw", "enemyEngeneer" };
			std::vector<Vector2f> enemySpawnPosRel = { {0.1, 0.1}, {0.9, 0.1}, {0.1, 0.9}, {0.9, 0.9} };
			auto enemy = scene->Spawn(enemyNames[std::rand() % enemyNames.size()]);
			auto enemyRelSpawnPos = enemySpawnPosRel[std::rand() % enemySpawnPosRel.size()];
			Vector2f enemySpawnPos = { sceneSize.x*enemyRelSpawnPos.x, sceneSize.y * enemyRelSpawnPos.y };
			enemy->ChangePosition(enemySpawnPos);
			clockEnemySpawn.restart();
		}
		cGameControl::Get()->Quant();
		scene->Quant(deltaQuant / 1000.0f); // ms -> sec
		CheckGameOver();
		clockQuant.restart();
	}
}
void cGame::CheckGameOver()
{
	
	if (clockGame.getElapsedTime().asSeconds() >= 60)
	{
		win = true;
		return;
	}
	if (cGameControl::Get()->ControledEntity()->Health() <= 0)
	{
		loose = false; 
		return;
	}
	else
	{	
		bool allDead = true;
		for (cEntity* entityToCheck : cScene::Get()->Entities())
		{
			if (entityToCheck->Name() == "tree")
			{
				if (entityToCheck->Health() > 0)
				{
					allDead = false;
					break;
				}
			}
		}
		loose = allDead;
	}
}
void cGame::Draw(sf::RenderWindow& window)
{
	if (!running) return;
	cGameControl::Get()->Draw(window);
}
