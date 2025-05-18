#include "cScene.h"
#include "cEntity.h"
#include "cGameControl.h"
#include "cGraphics.h"

using namespace std;
using namespace sf;

////////////////////////////////////////////////////////////////////////
class cSceneTexts
{
public:
	cSceneTexts() {}
	void Add(const std::string& _text, const sf::Vector2f& _pos, sf::Color _color, float _duration)
	{
		items.emplace_back(cItem(GetFont()));
		auto& item = items.back();
		item.duration = _duration;
		item.text.setString(_text);
		item.text.setFillColor(_color);
		item.text.setCharacterSize(50);
		item.position = _pos;
	}
	void Draw(sf::RenderWindow& window)
	{
		auto scene = cScene::Get();
		Vector2f screen_size = window.getView().getSize();
		float kx = screen_size.x / scene->GetSize().x;
		float ky = screen_size.y / scene->GetSize().y;
		for(auto it = items.begin(); it != items.end(); )
		{
			float passedSec = it->clock.getElapsedTime().asSeconds();
			if(passedSec > it->duration)
			{
				it = items.erase(it);
			}
			else
			{
				Vector2f pos = { it->position.x * kx, it->position.y * ky };
				it->text.setPosition(pos);
				// animate
				float k = 1.0f - passedSec / it->duration;
				it->text.setScale({ k, k });
				window.draw(it->text);
				++it;
			}
		}
	}

private:
	struct cItem
	{
		cItem(const sf::Font& _font) : text(_font)
		{
			clock.start();
		}
		sf::Text	 text;
		sf::Vector2f position;
		float		 duration = 2.0;
		sf::Clock	 clock;
	};
	std::vector<cItem> items;
};
static cSceneTexts scene_texts;
/////////////////////////////////////////////////////////////////////
class cSceneSprites
{
public:
	void Add(const std::string& _file, const sf::Vector2f& _pos, sf::Color _color, float _duration)
	{
		const Texture& texture = GetTexture(_file);
		items.emplace_back(cItem(texture));
		auto& item = items.back();
		item.duration = _duration;
		item.position = _pos;
	}
	void Draw(sf::RenderWindow& window)
	{
		auto scene = cScene::Get();
		Vector2f screen_size = window.getView().getSize();
		float kx = screen_size.x / scene->GetSize().x;
		float ky = screen_size.y / scene->GetSize().y;
		for (auto it = items.begin(); it != items.end();)
		{
			float passedSec = it->clock.getElapsedTime().asSeconds();
			if (passedSec > it->duration)
			{
				it = items.erase(it);
			}
			else
			{
				Vector2f pos = { it->position.x * kx, it->position.y * ky };
				it->sprite.setPosition(pos);
				//animation
				float k = 1.0f - passedSec / it->duration;
				it->sprite.setScale({ k, k });
				window.draw(it->sprite);
				++it;
			}
		}
	}
private:
	struct cItem
	{
		cItem(const Texture& _texture) : sprite(_texture)
		{
			clock.start();
		}
		sf::Sprite	 sprite;
		sf::Vector2f position;
		float		 duration = 2.0;
		sf::Clock	 clock;
	};
	std::vector<cItem> items;
};
static cSceneSprites scene_sprites;

cScene::cScene() : background(GetTexture(AssetsPath() + "Visuals/level1Background.png"))
{
}
cScene::~cScene()
{
	Clear();
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
void cScene::Clear()
{
	for (auto* e : entities)
	{
		delete e;
	}
	entities.clear();
}
void cScene::Quant(float deltaTimeSec)
{
	for(auto* e : entities)
	{
		e->Quant(deltaTimeSec);
	}
}
string cScene::Save() const
{
	string allEnt = "";
	for (int i = 0; i < entities.size(); i++)
	{
		auto e = entities[i];
		if (e->Health() > 0)
		{
			string name = e->Name();
			string positionX = std::to_string(e->GetPosition().x);
			string positionY = std::to_string(e->GetPosition().y);
			string health = std::to_string(e->Health());
			if (i == entities.size() - 1) allEnt += name + " " + positionX + " " + positionY + " " + health;
			else allEnt += name + " " + positionX + " " + positionY + " " + health + "\n";
		}
	}
	ShowText("Game Saved", entities[0]->GetPosition(), sf::Color::Green, 3);
	return allEnt;
}
void cScene::Load(std::vector<std::string>& _newEntities)
{
	Clear();
	for (auto s : _newEntities)
	{
		std::istringstream iss(s);
		std::string word;
		std::vector<std::string> entityParts;
		while (iss >> word)
		{
			entityParts.push_back(word);
		}
		cEntity* loadedEnt = new cEntity(entityParts[0]);
		Vector2f loadedEntPos = { std::stof(entityParts[1]),std::stof(entityParts[2]) };
		loadedEnt->ChangePosition(loadedEntPos);
		loadedEnt->SetHealth(std::stof(entityParts[3]));
		entities.push_back(loadedEnt);
	}
	cGameControl::Get()->ControledEntity(entities[0]);
	ShowText("Game Loaded", entities[0]->GetPosition(), sf::Color::Green, 3);
}
void cScene::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	for (auto* e : entities)
	{
		e->Draw(window);
	}
	scene_texts.Draw(window);
	scene_sprites.Draw(window);
}

cEntity* cScene::FindEntity(Vector2f pos)
{
	return nullptr;
}

void ShowText(const std::string& _text, const sf::Vector2f& _pos, sf::Color _color, float _duration)
{
	scene_texts.Add(_text, _pos, _color, _duration);
}


void ShowSprite(const std::string& _name, const sf::Vector2f& _pos, sf::Color _color, float _duration)
{
	scene_sprites.Add(_name, _pos, _color, _duration);
}
