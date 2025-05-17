#include "cGame.h"
#include "cScene.h"
#include "cEntity.h"
#include <memory>
#include <fstream>
#include "cGameControl.h"
#include "cWinScreen.h"
#include "cLooseScreen.h"


using namespace std;
float RandValue();

cGame* cGame::Get()
{
	static cGame game;
	return &game;
}
void cGame::Start()
{
	auto scene = cScene::Get();
	scene->Clear();
	auto hero = scene->Spawn("player");
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
	loose = false;
	win = false;
	pause = false;
	cWinScreen::ResetCounter();
	cLooseScreen::ResetCounter();
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
		if (clockEnemySpawn.getElapsedTime().asSeconds() >= RandValue()*10 + 5)
		{
			std::vector<string> enemyNames = { "enemyAxe", "enemySaw", "enemyChainSaw", "enemyKnife" };
			std::vector<Vector2f> enemySpawnPosRel = { {-0.1, -0.1}, {1.1, -0.1}, {-0.1, 1.1}, {1.1, 1.1}, {0.35, 1.1}, {0.35, -0.1}, {0.65, 1.1}, {0.65, -0.1}/*, {0.5, 0.5}, {0.3, 0.2}, {0.7, 0.4}, {0.6, 0.5}, {0.3, 0.1}, {0.1, 0.3}, {0.4, 0.8}*/ };
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
		loose = true; 
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
	cScene::Get()->Draw(window);
	if (!running) return;
	cGameControl::Get()->Draw(window);
}
const string& AssetsPath();
void cGame::Save(const std::string& _name) const
{
	string _path = AssetsPath() + "saves/" + _name + ".txt";
	std::ofstream file(_path);
	string whatToSave = cScene::Get()->Save();
	file.clear();
	file << whatToSave;
}

void cGame::Load(const std::string& _name)
{
	if (!Get()->IsRunning()) 
	{
		Get()->Start(); Get()->Pause(true);
	}
	string _path = AssetsPath() + "saves/" + _name + ".txt";
	auto file = std::fstream(_path);
	if (file.is_open())
	{
		vector<string> loadedEntities;
		std::string line;
		auto words = std::string();
		while (getline(file, words))
		{
			loadedEntities.push_back(words);
		}
		cScene::Get()->Load(loadedEntities);
	}
	else
	{
		std::cout << "Failed to load save from: " << _path;
	}
}
