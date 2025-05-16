#include "cScene.h"
#include "cEntity.h"
using namespace std;
using namespace sf;

const std::string& AssetsPath();
const sf::Texture& GetTexture(const std::string& path);
////////////////////////////////////////////////////////////////////////
class cSceneTexts
{
public:
	cSceneTexts() : font(AssetsPath() + "fonts/jersey25.ttf") {}
	void Add(const std::string& _text, const sf::Vector2f& _pos, sf::Color _color, float _duration)
	{
		items.emplace_back(cItem(font));
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
	const sf::Font font;
};
static cSceneTexts scene_texts;
/////////////////////////////////////////////////////////////////////
class cSceneSprites
{
public:
	cSceneSprites() {}
	~cSceneSprites()
	{
		for (auto e : items)
		{
			delete e.sprite;
		}
	}
	void Add(const std::string& _file, const sf::Vector2f& _pos, sf::Color _color, float _duration)
	{
		const Texture& texture = GetTexture(_file);
		auto sprite = new Sprite(texture);
		sprite->setPosition(_pos);
		items.emplace_back(cItem(sprite));
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
				delete it->sprite;
				it = items.erase(it);
			}
			else
			{
				Vector2f pos = { it->position.x * kx, it->position.y * ky };
				it->sprite->setPosition(pos);
				//animation
				float k = 1.0f - passedSec / it->duration;
				it->sprite->setScale({ k, k });
				window.draw(*it->sprite);
				++it;
			}
		}
	}
private:
	struct cItem
	{
		cItem(sf::Sprite* _sprite) : sprite(_sprite)
		{
			clock.start();
		}
		sf::Sprite* sprite = NULL;
		sf::Vector2f position;
		float		 duration = 2.0;
		sf::Clock	 clock;
	};
	std::vector<cItem> items;
	const sf::Font font;
};
static cSceneSprites scene_sprites;

cScene::cScene()
{
	backgroundTexture = Texture("../assets/Visuals/level1Background.png");
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
void cScene::Draw(sf::RenderWindow& window)
{
	window.draw(Sprite(backgroundTexture));
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
