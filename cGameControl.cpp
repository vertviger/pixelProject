#include "cGameControl.h"
#include "cScene.h"
#include "cEntity.h"
#include "cAction.h"
#include "cGraphics.h"

#include <memory>
#include <iostream>


using namespace std;
using namespace sf;

const string& AssetsPath();
std::vector<std::string> actions = { "actionFireball", "actionTeleport"/*, "actionHeal", "actionLightningStrike"*/};
cGameControl::cGameControl()
{
	string spritesPath = AssetsPath() + "Visuals/Sprites/";
	for (auto& action : actions)
	{
		const Texture& texture1 = GetTexture(spritesPath + "Actions/" + action + ".png");
		Sprite* actionSprite = new Sprite(texture1);
		actionSprite->setPosition({ 100, 600 });
		actionSprites.push_back(actionSprite);
	}
	const Texture& texture = GetTexture(spritesPath + "uiActionsFrame.png");
	slotsSprite = new Sprite(texture);
	slotsSprite->setPosition({ 100, 500 });
	selectedActionName = actions[0];
	/*const Texture& texture5 = GetTexture(spritesPath "hpBar.png");
	Sprite* hpBar = new Sprite(texture5);
	hpBar->setPosition({});
	const Texture& texture6 = GetTexture(spritesPath + "hpBar.png");
	Sprite* manaBar = new Sprite(texture6);
	manaBar->setPosition({});*/
}

cGameControl::~cGameControl()
{

}

cGameControl* cGameControl::Get()
{
	static cGameControl gameControl;
	return &gameControl;
}

sf::Vector2f MouseToScene(sf::Vector2i mousePosition);

void cGameControl::Quant()
{
	sf::Vector2f moveDirection(0.0f, 0.0f);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))		moveDirection.y = -1.0f; // up
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))	moveDirection.y = +1.0f; // down
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))		moveDirection.x = -1.0f; // left
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))	moveDirection.x = +1.0f; // right
	float l = moveDirection.length();
	if(l > 0.0f)
	{
		moveDirection /= l; // normalize
	}
	controlledEntity->SetMoveDirection(moveDirection);
	if (action && action->Do(target)) //Do returns true when action is finished
	{
		target = NULL;
		delete action;
		action = NULL;
	}
}

void cGameControl::Draw(RenderWindow& window)
{
	Vector2f windowSize = window.getView().getSize();
	float percent = controlledEntity->HealthPercentage();
	RectangleShape healthBar = RectangleShape({ 300 * percent, 50 });
	healthBar.setPosition(windowSize - healthBar.getSize());
	healthBar.setFillColor(Color::Red);
	window.draw(healthBar);
	float actionPosX = 24;
	float actionPosY = windowSize.y - (float)slotsSprite->getTexture().getSize().y;
	slotsSprite->setPosition({0, actionPosY});
	actionPosY += 40;
	for (auto& i : actionSprites)
	{
		window.draw(*i);
		i->setPosition({actionPosX, actionPosY});
		actionPosX += 74.5;
	}
	window.draw(*slotsSprite);
}

void cGameControl::EventHandle(optional<Event> event)
{
	if(auto const keyEvent = event->getIf<Event::KeyPressed>())
	{
		switch(keyEvent->code)
		{
			case Keyboard::Key::Num1: selectedActionName = actions[0]; break;
			case Keyboard::Key::Num2: selectedActionName = actions[1]; break;
			case Keyboard::Key::Num3: selectedActionName = actions[2]; break;
			case Keyboard::Key::Num4: selectedActionName = actions[3]; break;
		}
	}
	if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
	{
		if (mouseButtonPressed->button == sf::Mouse::Button::Left)
		{
			if (!action)
			{
				auto mouseScenePos = MouseToScene(mouseButtonPressed->position);
				for (auto e : cScene::Get()->Entities())
				{
					if (e->Bound().contains(mouseScenePos) && e->Name() != "tree" && e->Name() != "player")
					{
						target = e;
						action = new cAction(selectedActionName, controlledEntity);
					}
				}
			}
		}
	}
}