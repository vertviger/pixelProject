#include "cScene.h"
#include "cEntity.h"
using namespace std;
using namespace sf;

class cSceneTexts
{
public:
	cSceneTexts() : font("../assets/fonts/jersey25.ttf") {}
	void Add(const std::string& _text, const sf::Vector2f& _pos, sf::Color _color, float _duration)
	{
		items.emplace_back(eItem(font));
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
	struct eItem
	{
		eItem(const sf::Font& _font) : text(_font)
		{
			clock.start();
		}
		sf::Text	 text;
		sf::Vector2f position;
		float		 duration;
		sf::Clock	 clock;
	};
	std::vector<eItem> items;
	const sf::Font font;
};
static cSceneTexts scene_texts;

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
	scene_texts.Draw(window);
}

cEntity* cScene::FindEntity(Vector2f pos)
{
	return nullptr;
}

void ShowText(const std::string& _text, const sf::Vector2f& _pos, sf::Color _color, float _duration)
{
	scene_texts.Add(_text, _pos, _color, _duration);
}